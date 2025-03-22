#include "bitshift.h"
#include "CPU.h"

#include <cstdint>

static bool RL_r8(CPU* cpu, std::uint8_t* r8);
static bool RR_r8(CPU* cpu, std::uint8_t* r8);
static bool SRL_r8(CPU* cpu, std::uint8_t* r8);
static bool SWAP_r8(CPU* cpu, std::uint8_t* r8);
static bool RLC_r8(CPU* cpu, std::uint8_t* r8);
static bool RRC_r8(CPU* cpu, std::uint8_t* r8);
static bool SLA_r8(CPU* cpu, std::uint8_t* r8);
static bool SRA_r8(CPU* cpu, std::uint8_t* r8);

using BitShiftFunc = bool (*)(CPU*, std::uint8_t*);
static bool BITSHIFT_HL(CPU* cpu, BitShiftFunc func);

// RLCA
bool i07_RLCA(CPU* cpu) {
    RLC_r8(cpu, &cpu->A);
    cpu->SetFlagZero(false);
    return true;
}
// RRCA
bool i0F_RRCA(CPU* cpu) {
    RRC_r8(cpu, &cpu->A);
    cpu->SetFlagZero(false);
    return true;
}
// RLA
bool i17_RLA(CPU* cpu) {
    RL_r8(cpu, &cpu->A);
    cpu->SetFlagZero(false);
    return true;
}
// RRA
bool i1F_RRA(CPU* cpu) {
    RR_r8(cpu, &cpu->A);
    cpu->SetFlagZero(false);
    return true;
}

// RLC r8
bool iCB00_RLC_B(CPU* cpu) {
    return RLC_r8(cpu, &cpu->B);
}
bool iCB01_RLC_C(CPU* cpu) {
    return RLC_r8(cpu, &cpu->C);
}
bool iCB02_RLC_D(CPU* cpu) {
    return RLC_r8(cpu, &cpu->D);
}
bool iCB03_RLC_E(CPU* cpu) {
    return RLC_r8(cpu, &cpu->E);
}
bool iCB04_RLC_H(CPU* cpu) {
    return RLC_r8(cpu, &cpu->H);
}
bool iCB05_RLC_L(CPU* cpu) {
    return RLC_r8(cpu, &cpu->L);
}
bool iCB07_RLC_A(CPU* cpu) {
    return RLC_r8(cpu, &cpu->A);
}
// RLC [HL]
bool iCB06_RLC_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, RLC_r8);
}

// RRC r8
bool iCB08_RRC_B(CPU* cpu) {
    return RRC_r8(cpu, &cpu->B);
}
bool iCB09_RRC_C(CPU* cpu) {
    return RRC_r8(cpu, &cpu->C);
}
bool iCB0A_RRC_D(CPU* cpu) {
    return RRC_r8(cpu, &cpu->D);
}
bool iCB0B_RRC_E(CPU* cpu) {
    return RRC_r8(cpu, &cpu->E);
}
bool iCB0C_RRC_H(CPU* cpu) {
    return RRC_r8(cpu, &cpu->H);
}
bool iCB0D_RRC_L(CPU* cpu) {
    return RRC_r8(cpu, &cpu->L);
}
bool iCB0F_RRC_A(CPU* cpu) {
    return RRC_r8(cpu, &cpu->A);
}
// RRC [HL]
bool iCB0E_RRC_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, RRC_r8);
}

// RL r8
bool iCB10_RL_B(CPU* cpu) {
    return RL_r8(cpu, &cpu->B);
}
bool iCB11_RL_C(CPU* cpu) {
    return RL_r8(cpu, &cpu->C);
}
bool iCB12_RL_D(CPU* cpu) {
    return RL_r8(cpu, &cpu->D);
}
bool iCB13_RL_E(CPU* cpu) {
    return RL_r8(cpu, &cpu->E);
}
bool iCB14_RL_H(CPU* cpu) {
    return RL_r8(cpu, &cpu->H);
}
bool iCB15_RL_L(CPU* cpu) {
    return RL_r8(cpu, &cpu->L);
}
bool iCB17_RL_A(CPU* cpu) {
    return RL_r8(cpu, &cpu->A);
}
// RL [HL]
bool iCB16_RL_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, RL_r8);
}

// RR r8
bool iCB18_RR_B(CPU* cpu) {
    return RR_r8(cpu, &cpu->B);
}
bool iCB19_RR_C(CPU* cpu) {
    return RR_r8(cpu, &cpu->C);
}
bool iCB1A_RR_D(CPU* cpu) {
    return RR_r8(cpu, &cpu->D);
}
bool iCB1B_RR_E(CPU* cpu) {
    return RR_r8(cpu, &cpu->E);
}
bool iCB1C_RR_H(CPU* cpu) {
    return RR_r8(cpu, &cpu->H);
}
bool iCB1D_RR_L(CPU* cpu) {
    return RR_r8(cpu, &cpu->L);
}
bool iCB1F_RR_A(CPU* cpu) {
    return RR_r8(cpu, &cpu->A);
}
// RR [HL]
bool iCB1E_RR_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, RR_r8);
}

// SLA r8
bool iCB20_SLA_B(CPU* cpu) {
    return SLA_r8(cpu, &cpu->B);
}
bool iCB21_SLA_C(CPU* cpu) {
    return SLA_r8(cpu, &cpu->C);
}
bool iCB22_SLA_D(CPU* cpu) {
    return SLA_r8(cpu, &cpu->D);
}
bool iCB23_SLA_E(CPU* cpu) {
    return SLA_r8(cpu, &cpu->E);
}
bool iCB24_SLA_H(CPU* cpu) {
    return SLA_r8(cpu, &cpu->H);
}
bool iCB25_SLA_L(CPU* cpu) {
    return SLA_r8(cpu, &cpu->L);
}
bool iCB27_SLA_A(CPU* cpu) {
    return SLA_r8(cpu, &cpu->A);
}
// SLA [HL]
bool iCB26_SLA_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, SLA_r8);
}

// SRA r8
bool iCB28_SRA_B(CPU* cpu) {
    return SRA_r8(cpu, &cpu->B);
}
bool iCB29_SRA_C(CPU* cpu) {
    return SRA_r8(cpu, &cpu->C);
}
bool iCB2A_SRA_D(CPU* cpu) {
    return SRA_r8(cpu, &cpu->D);
}
bool iCB2B_SRA_E(CPU* cpu) {
    return SRA_r8(cpu, &cpu->E);
}
bool iCB2C_SRA_H(CPU* cpu) {
    return SRA_r8(cpu, &cpu->H);
}
bool iCB2D_SRA_L(CPU* cpu) {
    return SRA_r8(cpu, &cpu->L);
}
bool iCB2F_SRA_A(CPU* cpu) {
    return SRA_r8(cpu, &cpu->A);
}
// SRA [HL]
bool iCB2E_SRA_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, SRA_r8);
}


// SWAP r8
bool iCB30_SWAP_B(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->B);
}
bool iCB31_SWAP_C(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->C);
}
bool iCB32_SWAP_D(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->D);
}
bool iCB33_SWAP_E(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->E);
}
bool iCB34_SWAP_H(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->H);
}
bool iCB35_SWAP_L(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->L);
}
bool iCB37_SWAP_A(CPU* cpu) {
    return SWAP_r8(cpu, &cpu->A);
}
// SWAP [HL]
bool iCB36_SWAP_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, SWAP_r8);
}

// SRL r8
bool iCB38_SRL_B(CPU* cpu) {
    return SRL_r8(cpu, &cpu->B);
}
bool iCB39_SRL_C(CPU* cpu) {
    return SRL_r8(cpu, &cpu->C);
}
bool iCB3A_SRL_D(CPU* cpu) {
    return SRL_r8(cpu, &cpu->D);
}
bool iCB3B_SRL_E(CPU* cpu) {
    return SRL_r8(cpu, &cpu->E);
}
bool iCB3C_SRL_H(CPU* cpu) {
    return SRL_r8(cpu, &cpu->H);
}
bool iCB3D_SRL_L(CPU* cpu) {
    return SRL_r8(cpu, &cpu->L);
}
bool iCB3F_SRL_A(CPU* cpu) {
    return SRL_r8(cpu, &cpu->A);
}
// SRL [HL]
bool iCB3E_SRL_HL(CPU* cpu) {
    return BITSHIFT_HL(cpu, SRL_r8);
}

bool RL_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    auto old_carry = cpu->FlagCarry();
    bool new_carry = value >= 0x80;
    auto result = static_cast<std::uint8_t>((value << 1) | old_carry);
    cpu->SetFlags(result == 0, false, false, new_carry);
    *r8 = result;
    return true;
}
bool RR_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    auto old_carry = cpu->FlagCarry();
    bool new_carry = value & 1;
    auto result = static_cast<std::uint8_t>((value >> 1) | (old_carry << 7));
    cpu->SetFlags(result == 0, false, false, new_carry);
    *r8 = result;
    return true;
}
bool SRL_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    bool new_carry = value & 1;
    auto result = static_cast<std::uint8_t>(value >> 1);
    cpu->SetFlags(result == 0, false, false, new_carry);
    *r8 = result;
    return true;
}
bool SWAP_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    auto lo = value & 0x0F;
    auto hi = value & 0xF0;
    value = (lo << 4) | (hi >> 4);
    cpu->SetFlags(value == 0, false, false, false);
    *r8 = value;
    return true;
}
bool RLC_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    bool carry = value >= 0x80;
    value = (value << 1) | carry;
    cpu->SetFlags(value == 0, false, false, carry);
    *r8 = value;
    return true;
}
bool RRC_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    bool carry = value & 1;
    value = (carry << 7) | (value >> 1);
    cpu->SetFlags(value == 0, false, false, carry);
    *r8 = value;
    return true;
}
bool SLA_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    bool new_carry = value >= 0x80;
    value <<= 1;
    cpu->SetFlags(value == 0, false, false, new_carry);
    *r8 = value;
    return true;
}
bool SRA_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    bool carry = value & 1;
    value = (value & 0x80) | (value >> 1);
    cpu->SetFlags(value == 0, false, false, carry);
    *r8 = value;
    return true;
}

bool BITSHIFT_HL(CPU* cpu, BitShiftFunc func) {
    auto bus = cpu->GetBus();
    auto address = cpu->HL();
    auto value = bus->Read8(address);
    bool result = func(cpu, &value);
    bus->Write8(address, value);
    return result;
}
