#ifndef MPGB_BITSHIFT_H
#define MPGB_BITSHIFT_H

class CPU;

bool i07_RLCA(CPU* cpu);
bool i0F_RRCA(CPU* cpu);

bool i17_RLA(CPU* cpu);
bool i1F_RRA(CPU* cpu);

bool iCB00_RLC_B(CPU* cpu);
bool iCB01_RLC_C(CPU* cpu);
bool iCB02_RLC_D(CPU* cpu);
bool iCB03_RLC_E(CPU* cpu);
bool iCB04_RLC_H(CPU* cpu);
bool iCB05_RLC_L(CPU* cpu);
bool iCB06_RLC_HL(CPU* cpu);
bool iCB07_RLC_A(CPU* cpu);
bool iCB08_RRC_B(CPU* cpu);
bool iCB09_RRC_C(CPU* cpu);
bool iCB0A_RRC_D(CPU* cpu);
bool iCB0B_RRC_E(CPU* cpu);
bool iCB0C_RRC_H(CPU* cpu);
bool iCB0D_RRC_L(CPU* cpu);
bool iCB0E_RRC_HL(CPU* cpu);
bool iCB0F_RRC_A(CPU* cpu);

bool iCB10_RL_B(CPU* cpu);
bool iCB11_RL_C(CPU* cpu);
bool iCB12_RL_D(CPU* cpu);
bool iCB13_RL_E(CPU* cpu);
bool iCB14_RL_H(CPU* cpu);
bool iCB15_RL_L(CPU* cpu);
bool iCB16_RL_HL(CPU* cpu);
bool iCB17_RL_A(CPU* cpu);
bool iCB18_RR_B(CPU* cpu);
bool iCB19_RR_C(CPU* cpu);
bool iCB1A_RR_D(CPU* cpu);
bool iCB1B_RR_E(CPU* cpu);
bool iCB1C_RR_H(CPU* cpu);
bool iCB1D_RR_L(CPU* cpu);
bool iCB1E_RR_HL(CPU* cpu);
bool iCB1F_RR_A(CPU* cpu);

bool iCB20_SLA_B(CPU* cpu);
bool iCB21_SLA_C(CPU* cpu);
bool iCB22_SLA_D(CPU* cpu);
bool iCB23_SLA_E(CPU* cpu);
bool iCB24_SLA_H(CPU* cpu);
bool iCB25_SLA_L(CPU* cpu);
bool iCB26_SLA_HL(CPU* cpu);
bool iCB27_SLA_A(CPU* cpu);
bool iCB28_SRA_B(CPU* cpu);
bool iCB29_SRA_C(CPU* cpu);
bool iCB2A_SRA_D(CPU* cpu);
bool iCB2B_SRA_E(CPU* cpu);
bool iCB2C_SRA_H(CPU* cpu);
bool iCB2D_SRA_L(CPU* cpu);
bool iCB2E_SRA_HL(CPU* cpu);
bool iCB2F_SRA_A(CPU* cpu);

bool iCB30_SWAP_B(CPU* cpu);
bool iCB31_SWAP_C(CPU* cpu);
bool iCB32_SWAP_D(CPU* cpu);
bool iCB33_SWAP_E(CPU* cpu);
bool iCB34_SWAP_H(CPU* cpu);
bool iCB35_SWAP_L(CPU* cpu);
bool iCB36_SWAP_HL(CPU* cpu);
bool iCB37_SWAP_A(CPU* cpu);
bool iCB38_SRL_B(CPU* cpu);
bool iCB39_SRL_C(CPU* cpu);
bool iCB3A_SRL_D(CPU* cpu);
bool iCB3B_SRL_E(CPU* cpu);
bool iCB3C_SRL_H(CPU* cpu);
bool iCB3D_SRL_L(CPU* cpu);
bool iCB3E_SRL_HL(CPU* cpu);
bool iCB3F_SRL_A(CPU* cpu);

#endif
