#include <mpgb/instr/arithmetic16.h>
#include <mpgb/CPU.h>
#include <mpgb/instr/utils.h>

static bool ADD_HL_r16(CPU* cpu, std::uint16_t r16);
static bool INC_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo);
static bool DEC_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo);

// ADD HL,r16
bool i09_ADD_HL_BC(CPU* cpu) {
    return ADD_HL_r16(cpu, cpu->BC());
}
bool i19_ADD_HL_DE(CPU* cpu) {
    return ADD_HL_r16(cpu, cpu->DE());
}
bool i29_ADD_HL_HL(CPU* cpu) {
    return ADD_HL_r16(cpu, cpu->HL());
}
bool i39_ADD_HL_SP(CPU* cpu) {
    return ADD_HL_r16(cpu, cpu->SP);
}

// DEC r16
bool i0B_DEC_BC(CPU* cpu) {
    return DEC_r16(cpu, &cpu->B, &cpu->C);
}
bool i1B_DEC_DE(CPU* cpu) {
    return DEC_r16(cpu, &cpu->D, &cpu->E);
}
bool i2B_DEC_HL(CPU* cpu) {
    return DEC_r16(cpu, &cpu->H, &cpu->L);
}
// DEC SP
bool i3B_DEC_SP(CPU* cpu) {
    cpu->SP--;
    return true;
}

// INC r16
bool i03_INC_BC(CPU* cpu) {
    return INC_r16(cpu, &cpu->B, &cpu->C);
}
bool i13_INC_DE(CPU* cpu) {
    return INC_r16(cpu, &cpu->D, &cpu->E);
}
bool i23_INC_HL(CPU* cpu) {
    return INC_r16(cpu, &cpu->H, &cpu->L);
}

bool ADD_HL_r16(CPU* cpu, std::uint16_t r16) {
    auto hl = cpu->HL();
    auto result = hl + r16;
    auto half = (hl & 0xFFF) + (r16 & 0xFFF);
    hl = static_cast<std::uint16_t>(result);

    cpu->SetFlagSubtract(false);
    cpu->SetFlagHalfCarry(half > 0xFFF);
    cpu->SetFlagCarry(result > 0xFFFF);
    cpu->SetHL(hl);

    return true;
}

bool INC_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo) {
    auto r16 = to_r16(*hi, *lo);
    r16++;
    to_r8(r16, hi, lo);

    return true;
}
bool DEC_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo) {
    auto r16 = to_r16(*hi, *lo);
    r16--;
    to_r8(r16, hi, lo);

    return true;
}
