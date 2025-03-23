#ifndef MPGB_LOAD_H
#define MPGB_LOAD_H

class CPU;

bool i01_LD_BC_n16(CPU* cpu);
bool i02_LD_BC_A(CPU* cpu);
bool i06_LD_B_n8(CPU* cpu);
bool i0A_LD_A_BC(CPU* cpu);
bool i0E_LD_C_n8(CPU* cpu);

bool i11_LD_DE_n16(CPU* cpu);
bool i12_LD_DE_A(CPU* cpu);
bool i16_LD_D_n8(CPU* cpu);
bool i1E_LD_E_n8(CPU* cpu);
bool i1A_LD_A_DE(CPU* cpu);

bool i21_LD_HL_n16(CPU* cpu);
bool i22_LD_HLI_A(CPU* cpu);
bool i26_LD_H_n8(CPU* cpu);
bool i2A_LD_A_HLI(CPU* cpu);
bool i2E_LD_L_n8(CPU* cpu);

bool i32_LD_HLD_A(CPU* cpu);
bool i36_LD_HL_n8(CPU* cpu);
bool i3A_LD_A_HLD(CPU* cpu);
bool i3E_LD_A_n8(CPU* cpu);

bool i40_LD_B_B(CPU* cpu);
bool i41_LD_B_C(CPU* cpu);
bool i42_LD_B_D(CPU* cpu);
bool i43_LD_B_E(CPU* cpu);
bool i44_LD_B_H(CPU* cpu);
bool i45_LD_B_L(CPU* cpu);
bool i46_LD_B_HL(CPU* cpu);
bool i47_LD_B_A(CPU* cpu);
bool i48_LD_C_B(CPU* cpu);
bool i49_LD_C_C(CPU* cpu);
bool i4A_LD_C_D(CPU* cpu);
bool i4B_LD_C_E(CPU* cpu);
bool i4C_LD_C_H(CPU* cpu);
bool i4D_LD_C_L(CPU* cpu);
bool i4E_LD_C_HL(CPU* cpu);
bool i4F_LD_C_A(CPU* cpu);

bool i50_LD_D_B(CPU* cpu);
bool i51_LD_D_C(CPU* cpu);
bool i52_LD_D_D(CPU* cpu);
bool i53_LD_D_E(CPU* cpu);
bool i54_LD_D_H(CPU* cpu);
bool i55_LD_D_L(CPU* cpu);
bool i56_LD_D_HL(CPU* cpu);
bool i57_LD_D_A(CPU* cpu);
bool i58_LD_E_B(CPU* cpu);
bool i59_LD_E_C(CPU* cpu);
bool i5A_LD_E_D(CPU* cpu);
bool i5B_LD_E_E(CPU* cpu);
bool i5C_LD_E_H(CPU* cpu);
bool i5D_LD_E_L(CPU* cpu);
bool i5E_LD_E_HL(CPU* cpu);
bool i5F_LD_E_A(CPU* cpu);

bool i60_LD_H_B(CPU* cpu);
bool i61_LD_H_C(CPU* cpu);
bool i62_LD_H_D(CPU* cpu);
bool i63_LD_H_E(CPU* cpu);
bool i64_LD_H_H(CPU* cpu);
bool i65_LD_H_L(CPU* cpu);
bool i66_LD_H_HL(CPU* cpu);
bool i67_LD_H_A(CPU* cpu);
bool i68_LD_L_B(CPU* cpu);
bool i69_LD_L_C(CPU* cpu);
bool i6A_LD_L_D(CPU* cpu);
bool i6B_LD_L_E(CPU* cpu);
bool i6C_LD_L_H(CPU* cpu);
bool i6D_LD_L_L(CPU* cpu);
bool i6E_LD_H_HL(CPU* cpu);
bool i6F_LD_L_A(CPU* cpu);

bool i70_LD_HL_B(CPU* cpu);
bool i71_LD_HL_C(CPU* cpu);
bool i72_LD_HL_D(CPU* cpu);
bool i73_LD_HL_E(CPU* cpu);
bool i74_LD_HL_H(CPU* cpu);
bool i75_LD_HL_L(CPU* cpu);
bool i77_LD_HL_A(CPU* cpu);
bool i78_LD_A_B(CPU* cpu);
bool i79_LD_A_C(CPU* cpu);
bool i7A_LD_A_D(CPU* cpu);
bool i7B_LD_A_E(CPU* cpu);
bool i7C_LD_A_H(CPU* cpu);
bool i7D_LD_A_L(CPU* cpu);
bool i7E_LD_A_HL(CPU* cpu);
bool i7F_LD_A_A(CPU* cpu);

bool iE0_LDH_a8_A(CPU* cpu);
bool iE2_LDH_C_A(CPU* cpu);
bool iEA_LD_a16_A(CPU* cpu);

bool iF0_LDH_A_a8(CPU* cpu);
bool iF2_LDH_A_C(CPU* cpu);
bool iFA_LD_A_a16(CPU* cpu);

#endif
