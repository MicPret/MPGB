#ifndef MPGB_JUMPS_H
#define MPGB_JUMPS_H

class CPU;

bool i18_JR_e8(CPU* cpu);

bool i20_JR_NZ_e8(CPU* cpu);
bool i28_JR_Z_e8(CPU* cpu);

bool i30_JR_NC_e8(CPU* cpu);
bool i38_JR_C_e8(CPU* cpu);

bool iC0_RET_NZ(CPU* cpu);
bool iC2_JP_NZ_a16(CPU* cpu);
bool iC3_JP_n16(CPU* cpu);
bool iC4_CALL_NZ_a16(CPU* cpu);
bool iC7_RST_00(CPU* cpu);
bool iC8_RET_Z(CPU* cpu);
bool iC9_RET(CPU* cpu);
bool iCA_JP_Z_a16(CPU* cpu);
bool iCC_CALL_Z_a16(CPU* cpu);
bool iCD_CALL_a16(CPU* cpu);
bool iCF_RST_08(CPU* cpu);

bool iD0_RET_NC(CPU* cpu);
bool iD2_JP_NC_a16(CPU* cpu);
bool iD4_CALL_NC_a16(CPU* cpu);
bool iD7_RST_10(CPU* cpu);
bool iD8_RET_C(CPU* cpu);
bool iD9_RETI(CPU* cpu);
bool iDA_JP_C_a16(CPU* cpu);
bool iDC_CALL_C_a16(CPU* cpu);
bool iDF_RST_18(CPU* cpu);

bool iE7_RST_20(CPU* cpu);
bool iEF_RST_28(CPU* cpu);

bool iF7_RST_30(CPU* cpu);
bool iFF_RST_38(CPU* cpu);

bool iE9_JP_HL(CPU* cpu);

#endif
