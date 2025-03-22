#ifndef MPGB_STACK_H
#define MPGB_STACK_H

class CPU;

bool i08_LD_a16_SP(CPU* cpu);

bool i31_LD_SP_n16(CPU* cpu);
bool i33_INC_SP(CPU* cpu);

bool iC1_POP_BC(CPU* cpu);
bool iC5_PUSH_BC(CPU* cpu);

bool iD1_POP_DE(CPU* cpu);
bool iD5_PUSH_DE(CPU* cpu);

bool iE1_POP_HL(CPU* cpu);
bool iE5_PUSH_HL(CPU* cpu);
bool iE8_ADD_SP_e8(CPU* cpu);

bool iF1_POP_AF(CPU* cpu);
bool iF5_PUSH_AF(CPU* cpu);
bool iF8_LD_HL_SP_e8(CPU* cpu);
bool iF9_LD_SP_HL(CPU* cpu);

#endif
