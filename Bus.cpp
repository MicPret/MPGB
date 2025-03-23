#include <mpgb/Bus.h>
#include <mpgb/CPU.h>
#include <mpgb/PPU.h>
#include <mpgb/Print.h>
#include <mpgb/instr/utils.h>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

static const char* GetIOName(std::uint16_t address);
static std::uint8_t ReadError(const char* source, const char* msg, std::uint16_t address);

bool Bus::Load(const std::filesystem::path& boot) {
    std::ifstream file(boot, std::ios::binary);
    if (!file) {
        auto name = boot.string();
        PRINTF("Failed to load Boot ROM file: %s\n", name.c_str());
        return false;
    }
    std::vector<std::uint8_t> data(std::istreambuf_iterator<char>(file), {});
    if (data.empty()) {
        auto name = boot.string();
        PRINTF("Boot ROM file is empty: %s\n", name.c_str());
        return false;
    }
    std::copy(data.begin(), data.end(), m_BootROM.begin());
    return true;
}

bool Bus::EmulateFrame() {
    PPUResult state;
    do {
        unsigned cycles;
        Instruction instr = m_CPU->NextInstruction();
        if (instr.cycles.taken > m_PPU->DotsBeforeNextState()) {
            state = m_PPU->Tick(instr.cycles.taken);
            cycles = m_CPU->Tick();
        } else {
            cycles = m_CPU->Tick();
            state = m_PPU->Tick(cycles);
        }
        m_DMA.Tick(cycles);
        if (cycles == -1 || state == PPUStop)
            return false;
    } while (state != PPUDraw);

#ifndef __EMSCRIPTEN__
    constexpr float frame_time = 1.0f / 59.73f;
    float now;
    do {
        glfwPollEvents();
        now = glfwGetTime();
    } while ((now - m_Time) < frame_time);
    m_Time = now;
#endif
    return true;
}

void Bus::Signal(InterruptFlag interrupt) {
    m_CPU->IF |= interrupt;
}

void Bus::EmulateBoot() {
    m_BootSeq = false;
    m_CPU->EmulateBoot();
    m_PPU->EmulateBoot();
}

void Bus::Connect(CPU* cpu, PPU* ppu, GLFWwindow* window, Cartridge* cartridge) {
    assert(cpu);
    assert(ppu);
    SetCPU(cpu);
    cpu->SetBus(this);
    SetPPU(ppu);
    ppu->SetBus(this);
    ppu->SetWindow(window);
    SetCartridge(cartridge);
    m_Joypad.Connect(window);
    m_DMA.SetBus(this);
    m_Time = glfwGetTime();
}

std::uint8_t Bus::Read8(std::uint16_t address) const {
    if (address < 0x100)    // Boot             0x0000 ~ 0x00FF
        return m_BootSeq ? m_BootROM[address] : Read8Cartridge(address);
    if (address < 0x8000)   // ROM              0x0000 ~ 0x7FFF
        return Read8Cartridge(address);
    if (address < 0xA000)   // VRAM             0x8000 ~ 0x9FFF
        return m_PPU->ReadVRAM(address);
    if (address < 0xC000)   // External RAM     0xA000 ~ 0xBFFF
        return Read8Cartridge(address);
    if (address < 0xE000)   // WRAM             0xC000 ~ 0xDFFF
        return m_WRAM[address - 0xC000];
    if (address < 0xFE00)   // WRAM Echo        0xE000 ~ 0xFDFF
        return m_WRAM[address - 0xE000];
    if (address < 0xFEA0)   // OAM              0xFE00 ~ 0xFE9F
        return m_PPU->ReadOAM(address);
    if (address < 0xFF00)   // Not Usable       0xFEA0 ~ 0xFEFF
        return ReadError("Not Usable", "0xFEA0 ~ 0xFEFF is prohibited", address);
    if (address == 0xFF00)  // Joypad           0xFF00
        return m_Joypad.GetValue();
    if (address < 0xFF03)   // Serial transfer  0xFF01 ~ 0xFF02
        return ReadError("Serial transfer", "NOT IMPLEMENTED", address);
    if (address == 0xFF03)  // Undefined        0xFF03
        return ReadError(nullptr, nullptr, address);
    if (address == 0xFF04)  // DIV              0xFF04
        return m_CPU->DIV >> 8;
    if (address == 0xFF05)  // TIMA             0xFF05
        return m_CPU->TIMA;
    if (address == 0xFF06)  // TMA              0xFF06
        return m_CPU->TMA;
    if (address == 0xFF07)  // TAC              0xFF07
        return m_CPU->TAC;
    if (address < 0xFF0F)   // Undefined        0xFF08 ~ 0xFF0E
        return ReadError(nullptr, nullptr, address);
    if (address == 0xFF0F)  // Interrupt Flag   0xFF0F
        return m_CPU->IF;
    if (address <= 0xFF26)  // Audio            0xFF10 ~ 0xFF26
        return ReadError("Audio", "NOT IMPLEMENTED", address);
    if (address < 0xFF30)   // Undefined        0xFF27 ~ 0xFF2F
        return ReadError(nullptr, nullptr, address);
    if (address < 0xFF40)   // Wave pattern     0xFF30 ~ 0xFF3F
        return ReadError("Wave pattern", "NOT IMPLEMENTED", address);
    if (address == 0xFF46)  // DMA              0xFF46
        return ReadError("DMA", "NOT IMPLEMENTED", address);
    if (address <= 0xFF4B)  // PPU Registers    0xFF40 ~ 0xFF4B
        return m_PPU->ReadRegister(address);
    if (address == 0xFF50)  // Boot ROM Enable  0xFF50
        return !m_BootSeq;
    if (address < 0xFF80)   // Undefined        0xFF4C ~ 0xFF7F
        return ReadError("CGB I/O", nullptr, address);
    if (address < 0xFFFF)   // HRAM             0xFF80 ~ 0xFFFE
        return m_HRAM[address - 0xFF80];
    if (address == 0xFFFF)  // Interrupt Enable 0xFFFF
        return m_CPU->IE;
    return ReadError(nullptr, nullptr, address);
}

std::uint16_t Bus::Read16(std::uint16_t address) const {
    auto lo = Read8(address);
    auto hi = Read8(address + 1);
    return static_cast<std::uint16_t>((hi << 8) | lo);
}

bool Bus::Write8(std::uint16_t address, std::uint8_t value) {
    // ROM
    if (address < 0x8000) {
        bool success = Write8Cartridge(address, value);
        if (!success)
            fflush(stdout);
        return success;
    }
    // VRAM
    if (address < 0xA000) {
        return m_PPU->WriteVRAM(address, value);
    }
    // External RAM
    if (address < 0xC000) {
        bool success = Write8Cartridge(address, value);
        if (!success)
            fflush(stdout);
        return success;
    }
    // WRAM
    if (address < 0xE000) {
        m_WRAM[address - 0xC000] = value;
        return true;
    }
    // WRAM Echo
    if (address < 0xFE00) {
        m_WRAM[address - 0xE000] = value;
        return true;
    }
    // OAM
    if (address < 0xFEA0) {
        return m_PPU->WriteOAM(address, value);
    }
    // Not Usable
    if (address < 0xFF00) {
        PRINTF("[WRITE] [Not Usable]\t%04X | %02X\n", address, value);
        fflush(stdout);
        // exit(EXIT_FAILURE);
        return false;
    }
    // Joypad
    if (address == 0xFF00) {
        m_Joypad.SetValue(value);
        return true;
    }
    // Serial transfer
    if (address == 0xFF01) {
        m_SB = value;
        return true;
    }
    if (address == 0xFF02) {
        m_SC = value;
        if (value == 0x81) {
            PRINTF("[Output] %c\n", m_SB);
            m_SC &= ~(1 << 7);
            m_CPU->IF |= InterruptSerial;
        }
        return true;
    }
    // Undefined
    if (address == 0xFF03) [[unlikely]] {
        PRINTF("[WRITE] [Undefined]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // DIV
    if (address == 0xFF04) {
        m_CPU->DIV = 0;
        return true;
    }
    // TIMA
    if (address == 0xFF05) {
        m_CPU->TIMA = value;
        return true;
    }
    // TMA
    if (address == 0xFF06) {
        m_CPU->TMA = value;
        return true;
    }
    // TAC
    if (address == 0xFF07) {
        m_CPU->TAC = value;
        return true;
    }
    // Undefined
    if (address < 0xFF0F) [[unlikely]] {
        PRINTF("[WRITE] [Undefined]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // Interrupt Flag
    if (address == 0xFF0F) {
        m_CPU->IF = value;
        return true;
    }
    // Audio
    if (address <= 0xFF26) {
        // PRINTF("[WRITE] [Audio]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // Undefined
    if (address < 0xFF30) [[unlikely]] {
        PRINTF("[WRITE] [Undefined]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // Wave pattern
    if (address < 0xFF40) {
        // PRINTF("[WRITE] [Wave pattern]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // DMA
    if (address == 0xFF46) {
        m_DMA.InitiateTransfer(value << 8);
        return true;
    }
    // PPU Registers
    if (address <= 0xFF4B) {
        return m_PPU->WriteRegister(address, value);
    }
    // Boot ROM Enable
    if (address == 0xFF50) {
        PUTS("[WRITE] [Boot ROM DISABLE]");
        m_BootSeq = false;        
        return true;
    }
    // CGB I/O
    if (address < 0xFF80) {
        PRINTF("[WRITE] [CGB I/O]\t%04X | %02X\n", address, value);
        fflush(stdout);
        return false;
    }
    // HRAM
    if (address < 0xFFFF) {
        m_HRAM[address - 0xFF80] = value;
        return true;
    }
    // Interrupt Enable
    if (address == 0xFFFF) {
        m_CPU->IE = value;
        return true;
    }
    return false;
}

std::uint8_t Bus::Read8Cartridge(std::uint16_t address) const {
    return m_Cartridge ? m_Cartridge->Read8(address) : -1;
}

bool Bus::Write8Cartridge(std::uint16_t address, std::uint8_t value) {
    return m_Cartridge ? m_Cartridge->Write8(address, value) : false;
}

const char* GetIOName(std::uint16_t address) {
    constexpr auto invalid = "INVALID";
    auto lo = address & 0xFF;
    if (lo == 0x00) {
        return "Joypad input";
    } else if (lo <= 0x02) {
        return "Serial transfer";
    } else if (lo == 0x03) {
        return invalid;
    } else if (lo <= 0x07) {
        return "Timer and divider";
    } else if (lo < 0x0F) {
        return invalid;
    } else if (lo == 0x0F) {
        return "Interrupts";
    } else if (lo <= 0x26) {
        return "Audio";
    } else if (lo < 0x30) {
        return invalid;
    } else if (lo < 0x40) {
        return "Wave pattern";
    } else if (lo <= 0x4B) {
        return "LCD Control, Status, Position, Scrolling, Palettes";
    } else if (lo < 0x4F) {
        return invalid;
    } else if (lo == 0x4F) {
        return "VRAM Bank Select (CGB)";
    } else if (lo == 0x50) {
        return "Disable boot ROM";
    } else if (lo <= 0x55) {
        return "VRAM DMA (CGB)";
    } else if (lo < 0x68) {
        return invalid;
    } else if (lo <= 0x6B) {
        return "BG/OBJ Palettes (CGB)";
    } else if (lo == 0x70) {
        return "WRAM Bank Select (CGB)";
    }
    return invalid;
}

std::uint8_t ReadError(const char* source, const char* msg, std::uint16_t address) {
    const char* src = source ? source : "Undefined";
    const char* message = msg ? msg : "";
    PRINTF("[READ] [%s] %s\t%04X\n", src, message, address);
    fflush(stdout);
    return -1;
}

