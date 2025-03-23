#ifndef MPGB_GB_H
#define MPGB_GB_H

#include "Bus.h"
#include "Instruction.h"
#include "InterruptFlag.h"

#include <array>
#include <cstdint>

class CPU {
public:
    std::uint8_t A;     // AF
    std::uint8_t B;     // BC
    std::uint8_t C;     // BC
    std::uint8_t D;     // DE
    std::uint8_t E;     // DE
    std::uint8_t H;     // HL
    std::uint8_t L;     // HL
    std::uint8_t F;     // AF (Flags: ZNHC)
    std::uint16_t SP;
    std::uint16_t PC;
    std::uint8_t IE;    // Interrupt Enable
    std::uint8_t IF;    // Interrupt Flag

    std::uint16_t DIV;  // Divider register
    std::uint8_t TIMA;  // Timer counter
    std::uint8_t TMA;   // Timer modulo
    std::uint8_t TAC;   // Timer control

    bool Halt = false;

    CPU();
    unsigned Tick();
    std::uint8_t Fetch8();
    std::uint16_t Fetch16();
    Instruction NextInstruction() const;
    void EmulateBoot();
    
    std::uint16_t AF() const;
    std::uint16_t BC() const;
    std::uint16_t DE() const;
    std::uint16_t HL() const;
    bool IME() const;
    void SetAF(std::uint16_t value);
    void SetBC(std::uint16_t value);
    void SetDE(std::uint16_t value);
    void SetHL(std::uint16_t value);
    void SetIME(bool value);
    void SetIMENext();

    std::uint8_t FlagZero() const;
    std::uint8_t FlagSubtract() const;
    std::uint8_t FlagHalfCarry() const;
    std::uint8_t FlagCarry() const;
    void SetFlags(bool z, bool n, bool h, bool c);
    void SetFlagZero(bool value);
    void SetFlagSubtract(bool value);
    void SetFlagHalfCarry(bool value);
    void SetFlagCarry(bool value);

    const Bus* GetBus() const;
    Bus* GetBus();
    void SetBus(Bus* bus);
    
    void StackPush8(std::uint8_t value);
    void StackPush16(std::uint16_t value);
    void StackPush16(std::uint8_t hi, std::uint8_t lo);
    std::uint8_t StackPop8();
    std::uint16_t StackPop16();
private:
    Bus* m_Bus;
    std::uint8_t m_IME;
    unsigned m_Cycles = 0;

    std::uint8_t Flag(std::uint8_t bit) const;
    void SetFlag(std::uint8_t bit, bool value);
    unsigned HandleInterrupts();
    void UpdateTimer(unsigned cycles);
    void IncrementPC();
};

#endif
