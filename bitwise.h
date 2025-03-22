#ifndef MPGB_BITWISE_H
#define MPGB_BITWISE_H

class CPU;

bool i2F_CPL(CPU* cpu);

bool iA0_AND_A_B(CPU* cpu);
bool iA1_AND_A_C(CPU* cpu);
bool iA2_AND_A_D(CPU* cpu);
bool iA3_AND_A_E(CPU* cpu);
bool iA4_AND_A_H(CPU* cpu);
bool iA5_AND_A_L(CPU* cpu);
bool iA6_AND_A_HL(CPU* cpu);
bool iA7_AND_A_A(CPU* cpu);
bool iA8_XOR_A_B(CPU* cpu);
bool iA9_XOR_A_C(CPU* cpu);
bool iAA_XOR_A_D(CPU* cpu);
bool iAB_XOR_A_E(CPU* cpu);
bool iAC_XOR_A_H(CPU* cpu);
bool iAD_XOR_A_L(CPU* cpu);
bool iAE_XOR_A_HL(CPU* cpu);
bool iAF_XOR_A_A(CPU* cpu);

bool iB0_OR_A_B(CPU* cpu);
bool iB1_OR_A_C(CPU* cpu);
bool iB2_OR_A_D(CPU* cpu);
bool iB3_OR_A_E(CPU* cpu);
bool iB4_OR_A_H(CPU* cpu);
bool iB5_OR_A_L(CPU* cpu);
bool iB6_OR_A_HL(CPU* cpu);
bool iB7_OR_A_A(CPU* cpu);

bool iE6_AND_A_n8(CPU* cpu);
bool iEE_XOR_A_n8(CPU* cpu);

bool iF6_OR_A_n8(CPU* cpu);

#endif
