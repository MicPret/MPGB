#ifndef MPGB_BUS_H
#define MPGB_BUS_H

#include "Cartridge.h"
#include "DMA.h"
#include "InterruptFlag.h"
#include "Joypad.h"

#include <array>
#include <cstdint>
#include <filesystem>

class CPU;
class PPU;
struct GLFWwindow;

class Bus {
public:
    bool Load(const std::filesystem::path& boot);
    std::uint8_t Read8(std::uint16_t address) const;
    std::uint16_t Read16(std::uint16_t address) const;
    bool Write8(std::uint16_t address, std::uint8_t value);

    void Connect(CPU* cpu, PPU* ppu, GLFWwindow* window, Cartridge* cartridge = nullptr);
    bool EmulateFrame();
    void Signal(InterruptFlag interrupt);
    void EmulateBoot();

    constexpr void SetCPU(CPU* cpu) { m_CPU = cpu; }
    constexpr void SetPPU(PPU* ppu) { m_PPU = ppu; }
    constexpr void SetCartridge(Cartridge* cartridge) { m_Cartridge = cartridge; }
private:
    CPU* m_CPU = nullptr;
    PPU* m_PPU = nullptr;
    Cartridge* m_Cartridge = nullptr;
    float m_Time;
    bool m_BootSeq = true;
    DMA m_DMA;
    Joypad m_Joypad;
    std::uint8_t m_SB;
    std::uint8_t m_SC;
    std::array<std::uint8_t, 0xFF> m_BootROM;   // 0x0000 ~ 0x00FF (Boot ROM)
    std::array<std::uint8_t, 0x2000> m_WRAM;    // 0xC000 ~ 0xDFFF (Work RAM)
    std::array<std::uint8_t, 0x7F> m_HRAM;      // 0xFF80 ~ 0XFFFE (High RAM)

    std::uint8_t Read8Cartridge(std::uint16_t address) const;
    bool Write8Cartridge(std::uint16_t address, std::uint8_t value);
};

#endif
