#include <mpgb/instr/load.h>
#include <mpgb/CPU.h>

static bool LD_r8_r8(std::uint8_t* dest, std::uint8_t source);
static bool LD_r8_n8(CPU* cpu, std::uint8_t* r8);
static bool LD_r8_HL(CPU* cpu, std::uint8_t* r8);
static bool LD_r16_n16(CPU* cpu, std::uint16_t* r16);
static bool LD_HL_r8(CPU* cpu, std::uint8_t r8);
static bool LD_A_r16(CPU* cpu, std::uint16_t r16);
static bool LD_r16_A(CPU* cpu, std::uint16_t r16);

bool i02_LD_BC_A(CPU* cpu) {
    return LD_r16_A(cpu, cpu->BC());
}
bool i12_LD_DE_A(CPU* cpu) {
    return LD_r16_A(cpu, cpu->DE());
}

bool i47_LD_B_A(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->A);
}
bool i4F_LD_C_A(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->A);
}
bool i57_LD_D_A(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->A);
}
bool i60_LD_H_B(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->B);
}
bool i61_LD_H_C(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->C);
}
bool i62_LD_H_D(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->D);
}
bool i63_LD_H_E(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->E);
}
bool i64_LD_H_H(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->H);
}
bool i65_LD_H_L(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->L);
}
bool i67_LD_H_A(CPU* cpu) {
    return LD_r8_r8(&cpu->H, cpu->A);
}
bool i06_LD_B_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->B);
}
bool i0E_LD_C_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->C);
}
bool i16_LD_D_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->D);
}
bool i1E_LD_E_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->E);
}
bool i26_LD_H_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->H);
}
bool i2E_LD_L_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->L);
}
bool i3E_LD_A_n8(CPU* cpu) {
    return LD_r8_n8(cpu, &cpu->A);
}

bool i70_LD_HL_B(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->B);
}
bool i71_LD_HL_C(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->C);
}
bool i72_LD_HL_D(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->D);
}
bool i73_LD_HL_E(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->E);
}
bool i74_LD_HL_H(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->H);
}
bool i75_LD_HL_L(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->L);
}
bool i77_LD_HL_A(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->A);
}

bool i36_LD_HL_n8(CPU* cpu) {
    return LD_HL_r8(cpu, cpu->Fetch8());
}

bool i40_LD_B_B(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->B);
}
bool i41_LD_B_C(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->C);
}
bool i42_LD_B_D(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->D);
}
bool i43_LD_B_E(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->E);
}
bool i44_LD_B_H(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->H);
}
bool i45_LD_B_L(CPU* cpu) {
    return LD_r8_r8(&cpu->B, cpu->L);
}
bool i48_LD_C_B(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->B);
}
bool i49_LD_C_C(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->C);
}
bool i4A_LD_C_D(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->D);
}
bool i4B_LD_C_E(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->E);
}
bool i4C_LD_C_H(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->H);
}
bool i4D_LD_C_L(CPU* cpu) {
    return LD_r8_r8(&cpu->C, cpu->L);
}
bool i50_LD_D_B(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->B);
}
bool i51_LD_D_C(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->C);
}
bool i52_LD_D_D(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->D);
}
bool i53_LD_D_E(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->E);
}
bool i54_LD_D_H(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->H);
}
bool i55_LD_D_L(CPU* cpu) {
    return LD_r8_r8(&cpu->D, cpu->L);
}
bool i58_LD_E_B(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->B);
}
bool i59_LD_E_C(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->C);
}
bool i5A_LD_E_D(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->D);
}
bool i5B_LD_E_E(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->E);
}
bool i5C_LD_E_H(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->H);
}
bool i5D_LD_E_L(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->L);
}
bool i5F_LD_E_A(CPU* cpu) {
    return LD_r8_r8(&cpu->E, cpu->A);
}
bool i68_LD_L_B(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->B);
}
bool i69_LD_L_C(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->C);
}
bool i6A_LD_L_D(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->D);
}
bool i6B_LD_L_E(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->E);
}
bool i6C_LD_L_H(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->H);
}
bool i6D_LD_L_L(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->L);
}
bool i6F_LD_L_A(CPU* cpu) {
    return LD_r8_r8(&cpu->L, cpu->A);
}
bool i78_LD_A_B(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->B);
}
bool i79_LD_A_C(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->C);
}
bool i7A_LD_A_D(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->D);
}
bool i7B_LD_A_E(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->E);
}
bool i7C_LD_A_H(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->H);
}
bool i7D_LD_A_L(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->L);
}
bool i7F_LD_A_A(CPU* cpu) {
    return LD_r8_r8(&cpu->A, cpu->A);
}

bool i0A_LD_A_BC(CPU* cpu) {
    return LD_A_r16(cpu, cpu->BC());
}
bool i1A_LD_A_DE(CPU* cpu) {
    return LD_A_r16(cpu, cpu->DE());
}

bool i01_LD_BC_n16(CPU* cpu) {
    std::uint16_t r16;
    LD_r16_n16(cpu, &r16);
    cpu->SetBC(r16);
    return true;
}
bool i11_LD_DE_n16(CPU* cpu) {
    std::uint16_t r16;
    LD_r16_n16(cpu, &r16);
    cpu->SetDE(r16);
    return true;
}
bool i21_LD_HL_n16(CPU* cpu) {
    std::uint16_t r16;
    LD_r16_n16(cpu, &r16);
    cpu->SetHL(r16);
    return true;
}

bool i22_LD_HLI_A(CPU* cpu) {
    auto address = cpu->HL();
    cpu->GetBus()->Write8(address, cpu->A);
    cpu->SetHL(address + 1);
    return true;
}
bool i32_LD_HLD_A(CPU* cpu) {
    auto address = cpu->HL();
    cpu->GetBus()->Write8(address, cpu->A);
    cpu->SetHL(address - 1);
    return true;
}
bool i2A_LD_A_HLI(CPU* cpu) {
    auto address = cpu->HL();
    cpu->A = cpu->GetBus()->Read8(address);
    cpu->SetHL(address + 1);
    return true;
}
bool i3A_LD_A_HLD(CPU* cpu) {
    auto address = cpu->HL();
    cpu->A = cpu->GetBus()->Read8(address);
    cpu->SetHL(address - 1);
    return true;
}

bool iE0_LDH_a8_A(CPU* cpu) {
    auto offset = cpu->Fetch8();
    auto address = 0xFF00 | offset;
    cpu->GetBus()->Write8(address, cpu->A);
    return true;
}

bool iE2_LDH_C_A(CPU* cpu) {
    std::uint16_t address = 0xFF00 | cpu->C;
    cpu->GetBus()->Write8(address, cpu->A);
    return true;
}

bool iEA_LD_a16_A(CPU* cpu) {
    std::uint16_t address = cpu->Fetch16();
    cpu->GetBus()->Write8(address, cpu->A);
    return true;
}
bool iFA_LD_A_a16(CPU* cpu) {
    std::uint16_t address = cpu->Fetch16();
    cpu->A = cpu->GetBus()->Read8(address);
    return true;
}

// LD r8,[HL]
bool i46_LD_B_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->B);
}
bool i4E_LD_C_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->C);
}
bool i56_LD_D_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->D);
}
bool i5E_LD_E_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->E);
}
bool i66_LD_H_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->H);
}
bool i6E_LD_H_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->L);
}
bool i7E_LD_A_HL(CPU* cpu) {
    return LD_r8_HL(cpu, &cpu->A);
}

bool iF0_LDH_A_a8(CPU* cpu) {
    auto offset = cpu->Fetch8();
    auto address = static_cast<std::uint16_t>(0xFF00 | offset);
    cpu->A = cpu->GetBus()->Read8(address);
    return true;
}
bool iF2_LDH_A_C(CPU* cpu) {
    std::uint16_t address = 0xFF00 | cpu->C;
    cpu->A = cpu->GetBus()->Read8(address);
    return true;
}




bool LD_r8_r8(std::uint8_t* dest, std::uint8_t source) {
    *dest = source;
    return true;
}
bool LD_r8_n8(CPU* cpu, std::uint8_t* r8) {
    *r8 = cpu->Fetch8();
    return true;
}
bool LD_r8_HL(CPU* cpu, std::uint8_t* r8) {
    auto address = cpu->HL();
    *r8 = cpu->GetBus()->Read8(address);
    return true;
}
bool LD_r16_n16(CPU* cpu, std::uint16_t* r16) {
    *r16 = cpu->Fetch16();
    return true;
}
bool LD_HL_r8(CPU* cpu, std::uint8_t r8) {
    cpu->GetBus()->Write8(cpu->HL(), r8);
    return true;
}
bool LD_A_r16(CPU* cpu, std::uint16_t r16) {
    cpu->A = cpu->GetBus()->Read8(r16);
    return true;
}
bool LD_r16_A(CPU* cpu, std::uint16_t r16) {
    cpu->GetBus()->Write8(r16, cpu->A);
    return true;
}

