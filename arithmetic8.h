#ifndef MPGB_ARITHMETIC8_H
#define MPGB_ARITHMETIC8_H

class CPU;

bool i04_INC_B(CPU* cpu);
bool i05_DEC_B(CPU* cpu);
bool i0C_INC_C(CPU* cpu);
bool i0D_DEC_C(CPU* cpu);

bool i14_INC_D(CPU* cpu);
bool i15_DEC_D(CPU* cpu);
bool i1C_INC_E(CPU* cpu);
bool i1D_DEC_E(CPU* cpu);

bool i24_INC_H(CPU* cpu);
bool i25_DEC_H(CPU* cpu);
bool i2C_INC_L(CPU* cpu);
bool i2D_DEC_L(CPU* cpu);

bool i34_INC_HL(CPU* cpu); // INC [HL]
bool i35_DEC_HL(CPU* cpu); // DEC [HL]
bool i3C_INC_A(CPU* cpu);
bool i3D_DEC_A(CPU* cpu);

bool i80_ADD_A_B(CPU* cpu);
bool i81_ADD_A_C(CPU* cpu);
bool i82_ADD_A_D(CPU* cpu);
bool i83_ADD_A_E(CPU* cpu);
bool i84_ADD_A_H(CPU* cpu);
bool i85_ADD_A_L(CPU* cpu);
bool i86_ADD_A_HL(CPU* cpu); // ADD A,[HL]
bool i87_ADD_A_A(CPU* cpu);
bool i88_ADC_A_B(CPU* cpu);
bool i89_ADC_A_C(CPU* cpu);
bool i8A_ADC_A_D(CPU* cpu);
bool i8B_ADC_A_E(CPU* cpu);
bool i8C_ADC_A_H(CPU* cpu);
bool i8D_ADC_A_L(CPU* cpu);
bool i8E_ADC_A_HL(CPU* cpu); // ADC A,[HL]
bool i8F_ADC_A_A(CPU* cpu);

bool i90_SUB_A_B(CPU* cpu);
bool i91_SUB_A_C(CPU* cpu);
bool i92_SUB_A_D(CPU* cpu);
bool i93_SUB_A_E(CPU* cpu);
bool i94_SUB_A_H(CPU* cpu);
bool i95_SUB_A_L(CPU* cpu);
bool i96_SUB_A_HL(CPU* cpu);
bool i97_SUB_A_A(CPU* cpu);
bool i98_SBC_A_B(CPU* cpu);
bool i99_SBC_A_C(CPU* cpu);
bool i9A_SBC_A_D(CPU* cpu);
bool i9B_SBC_A_E(CPU* cpu);
bool i9C_SBC_A_H(CPU* cpu);
bool i9D_SBC_A_L(CPU* cpu);
bool i9E_SBC_A_HL(CPU* cpu);
bool i9F_SBC_A_A(CPU* cpu);

bool iB8_CP_A_B(CPU * cpu);
bool iB9_CP_A_C(CPU * cpu);
bool iBA_CP_A_D(CPU * cpu);
bool iBB_CP_A_E(CPU * cpu);
bool iBC_CP_A_H(CPU * cpu);
bool iBD_CP_A_L(CPU * cpu);
bool iBE_CP_A_HL(CPU* cpu);
bool iBF_CP_A_A(CPU * cpu);

bool iC6_ADD_A_n8(CPU* cpu);
bool iCE_ADC_A_n8(CPU* cpu);

bool iD6_SUB_A_n8(CPU* cpu);
bool iDE_SBC_A_n8(CPU* cpu);

bool iFE_CP_A_n8(CPU* cpu);

#endif
