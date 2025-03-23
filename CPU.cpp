#include <mpgb/CPU.h>
#include <mpgb/Cycles.h>
#include <mpgb/InstructionFunc.h>
#include <mpgb/instr/utils.h>

#include <cstdio>
#include <iostream>

CPU::CPU() : PC(0), m_IME(0), IE(0), IF(0) {}

unsigned CPU::Tick() {
    unsigned cycles_interrupt = 0;
    cycles_interrupt = HandleInterrupts();
    if (Halt) {
        unsigned cycles = 4 + cycles_interrupt;
        UpdateTimer(cycles);
        return cycles;
    }

    Instruction instr = NextInstruction();
    auto current_address = PC;
    // printf("%04X: %02X\n", current_address, instr.opcode);
    auto opcode = static_cast<unsigned>(Fetch8());
    if (opcode == 0xCB) {
        auto next = Fetch8();
        opcode = 0x100u | next;
    }
    if (!instr.func) {
        printf("%04X: ", current_address);
        if (opcode >= 0x100) {
            printf("%02X", 0xCB);
        }
        printf("%02X [Not implemented]\n", opcode & 0xFF);
        return -1;
    }
    auto cycles = cycles_interrupt + instr.cycles.untaken;
    UpdateTimer(cycles);
    bool taken = instr.func(this);
    if (taken) {
        UpdateTimer(instr.cycles.taken - instr.cycles.untaken);
    }
    if (m_IME == 1) {
        m_IME = 2;
    }
    return cycles;
}

std::uint16_t CPU::AF() const {
    return to_r16(A, F);
}
std::uint16_t CPU::BC() const {
    return to_r16(B, C);
}
std::uint16_t CPU::DE() const {
    return to_r16(D, E);
}
std::uint16_t CPU::HL() const {
    return to_r16(H, L);
}
bool CPU::IME() const {
    return m_IME == 2;
}
void CPU::SetAF(std::uint16_t value) {
    to_r8(value, &A, &F);
}
void CPU::SetBC(std::uint16_t value) {
    to_r8(value, &B, &C);
}
void CPU::SetDE(std::uint16_t value) {
    to_r8(value, &D, &E);
}
void CPU::SetHL(std::uint16_t value) {
    to_r8(value, &H, &L);
}
void CPU::SetIME(bool value) {
    m_IME = value ? 2 : 0;
}
void CPU::SetIMENext() {
    if (m_IME == 0) {
        m_IME = 1;
    }
}

std::uint8_t CPU::Flag(std::uint8_t bit) const {
    return static_cast<std::uint8_t>(get_bit(F, bit));
}
void CPU::SetFlag(std::uint8_t bit, bool value) {
    F = set_bit(F, bit, value);
}
std::uint8_t CPU::FlagZero() const {
    return Flag(7);
}
std::uint8_t CPU::FlagSubtract() const {
    return Flag(6);
}
std::uint8_t CPU::FlagHalfCarry() const {
    return Flag(5);
}
std::uint8_t CPU::FlagCarry() const {
    return Flag(4);
}
void CPU::SetFlagZero(bool value) {
    SetFlag(7, value);
}
void CPU::SetFlagSubtract(bool value) {
    SetFlag(6, value);
}
void CPU::SetFlagHalfCarry(bool value) {
    SetFlag(5, value);
}
void CPU::SetFlagCarry(bool value) {
    SetFlag(4, value);
}
void CPU::SetFlags(bool z, bool n, bool h, bool c) {
    F = static_cast<std::uint8_t>((z << 7) | (n << 6) | (h << 5) | (c << 4));
}

const Bus* CPU::GetBus() const {
    return m_Bus;
}
Bus* CPU::GetBus() {
    return m_Bus;
}
void CPU::SetBus(Bus* bus) {
    m_Bus = bus;
}

std::uint8_t CPU::Fetch8() {
    auto result = m_Bus->Read8(PC);
    IncrementPC();
    return result;
}
std::uint16_t CPU::Fetch16() {
    auto lo = Fetch8();
    auto hi = Fetch8();
    return (hi << 8) | lo;
}
void CPU::IncrementPC() {
    // if (m_Halt == HaltBug) [[unlikely]] {
    //     m_Halt = HaltNone;
    // } else {
    //     PC++;
    // }
    PC++;
}

void CPU::StackPush8(std::uint8_t value) {
    m_Bus->Write8(--SP, value);
}
void CPU::StackPush16(std::uint16_t value) {
    std::uint8_t hi, lo;
    to_r8(value, &hi, &lo);
    StackPush16(hi, lo);
}
void CPU::StackPush16(std::uint8_t hi, std::uint8_t lo) {
    StackPush8(hi);
    StackPush8(lo);
}
std::uint8_t CPU::StackPop8() {
    return m_Bus->Read8(SP++);
}
std::uint16_t CPU::StackPop16() {
    auto lo = StackPop8();
    auto hi = StackPop8();
    return to_r16(hi, lo);
}

unsigned CPU::HandleInterrupts() {
    auto interrupts = IF & IE;
    if (interrupts == 0) {
        return 0;
    }
    if (Halt) {
        Halt = false;
    }
    if (!IME()) {
        return 0;
    }
    SetIME(false);
    StackPush16(PC);
    const char* name;
    if (interrupts & InterruptVBlank) {
        IF &= ~InterruptVBlank;
        PC = 0x40;
        name = "VBlank";
    } else if (interrupts & InterruptLCD) {
        IF &= ~InterruptLCD;
        PC = 0x48;
        name = "LCD";
    } else if (interrupts & InterruptTimer) {
        IF &= ~InterruptTimer;
        PC = 0x50;
        name = "Timer";
    } else if (interrupts & InterruptSerial) {
        IF &= ~InterruptSerial;
        PC = 0x58;
        name = "Serial";
    } else if (interrupts & InterruptJoypad) {
        IF &= ~InterruptJoypad;
        PC = 0x60;
        name = "Joypad";
    }
    // printf("[Interrupt handled] %s\n", name);
    return 20;
}

void CPU::UpdateTimer(unsigned cycles) {
    m_Cycles += cycles;
    DIV += cycles;
    if (TAC & 0b100) {
        constexpr std::array clocks = { 1024, 16, 64, 256 };
        auto clock = clocks[TAC & 0b11];
        if (m_Cycles > clock) {
            if (++TIMA == 0) {
                TIMA = TMA;
                IF |= InterruptTimer;
            }
            m_Cycles = m_Cycles % clock;
        }
    }
}

Instruction CPU::NextInstruction() const {
    unsigned opcode = m_Bus->Read8(PC);
    if (opcode == 0xCB) {
        unsigned next = /* m_Halt == HaltBug ? opcode : */ m_Bus->Read8(PC + 1);
        opcode = (opcode << 8) | next;
    }
    auto offset = opcode & 0x1FF;
    Instruction result;
    result.opcode = opcode;
    result.cycles = GetCyclesTable()[offset];
    result.func = GetInstructionFuncTable()[offset];
    return result;
}

void CPU::EmulateBoot() {
    PC = 0x100;
    SP = 0xFFFE;
    IE = 0;
    IF = 0;
    SetIME(false);
    SetFlags(true, false, false, false);
    A = 1;
    B = 0;
    C = 0x13;
    D = 0;
    E = 0xD8;
    H = 1;
    L = 0x4D;
}
