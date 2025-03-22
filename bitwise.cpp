#include "bitwise.h"
#include "CPU.h"

static bool AND_A_r8(CPU* cpu, std::uint8_t r8);
static bool XOR_A_r8(CPU* cpu, std::uint8_t r8);
static bool OR_A_r8(CPU* cpu, std::uint8_t r8);

// AND A,r8
bool iA0_AND_A_B(CPU* cpu) {
    return AND_A_r8(cpu, cpu->B);
}
bool iA1_AND_A_C(CPU* cpu) {
    return AND_A_r8(cpu, cpu->C);
}
bool iA2_AND_A_D(CPU* cpu) {
    return AND_A_r8(cpu, cpu->D);
}
bool iA3_AND_A_E(CPU* cpu) {
    return AND_A_r8(cpu, cpu->E);
}
bool iA4_AND_A_H(CPU* cpu) {
    return AND_A_r8(cpu, cpu->H);
}
bool iA5_AND_A_L(CPU* cpu) {
    return AND_A_r8(cpu, cpu->L);
}
bool iA7_AND_A_A(CPU* cpu) {
    return AND_A_r8(cpu, cpu->A);
}

// AND A,HL
bool iA6_AND_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    AND_A_r8(cpu, value);
    return true;
}

// CPL
bool i2F_CPL(CPU* cpu) {
    cpu->A = ~cpu->A;
    cpu->SetFlagSubtract(true);
    cpu->SetFlagHalfCarry(true);
    return true;
}

// XOR A,r8
bool iA8_XOR_A_B(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->B);
}
bool iA9_XOR_A_C(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->C);
}
bool iAA_XOR_A_D(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->D);
}
bool iAB_XOR_A_E(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->E);
}
bool iAC_XOR_A_H(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->H);
}
bool iAD_XOR_A_L(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->L);
}
bool iAE_XOR_A_HL(CPU* cpu) {
    auto value = cpu->GetBus()->Read8(cpu->HL());
    return XOR_A_r8(cpu, value);
}
bool iAF_XOR_A_A(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->A);
}

// OR A,r8
bool iB0_OR_A_B(CPU* cpu) {
    return OR_A_r8(cpu, cpu->B);
}
bool iB1_OR_A_C(CPU* cpu) {
    return OR_A_r8(cpu, cpu->C);
}
bool iB2_OR_A_D(CPU* cpu) {
    return OR_A_r8(cpu, cpu->D);
}
bool iB3_OR_A_E(CPU* cpu) {
    return OR_A_r8(cpu, cpu->E);
}
bool iB4_OR_A_H(CPU* cpu) {
    return OR_A_r8(cpu, cpu->H);
}
bool iB5_OR_A_L(CPU* cpu) {
    return OR_A_r8(cpu, cpu->L);
}
bool iB6_OR_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    return OR_A_r8(cpu, value);
}
bool iB7_OR_A_A(CPU* cpu) {
    return OR_A_r8(cpu, cpu->A);
}


bool iE6_AND_A_n8(CPU* cpu) {
    return AND_A_r8(cpu, cpu->Fetch8());
}
bool iEE_XOR_A_n8(CPU* cpu) {
    return XOR_A_r8(cpu, cpu->Fetch8());
}
bool iF6_OR_A_n8(CPU* cpu) {
    return OR_A_r8(cpu, cpu->Fetch8());
}


bool AND_A_r8(CPU* cpu, std::uint8_t r8) {
    cpu->A &= r8;
    cpu->SetFlags(cpu->A == 0, false, true, false);
    return true;
}

bool XOR_A_r8(CPU* cpu, std::uint8_t r8) {
    cpu->A ^= r8;
    cpu->SetFlags(cpu->A == 0, false, false, false);
    return true;
}

bool OR_A_r8(CPU* cpu, std::uint8_t r8) {
    cpu->A |= r8;
    cpu->SetFlags(cpu->A == 0, false, false, false);
    return true;
}
