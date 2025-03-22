#ifndef MPGB_ARITHMETIC16_H
#define MPGB_ARITHMETIC16_H

class CPU;

bool i03_INC_BC(CPU* cpu);
bool i09_ADD_HL_BC(CPU* cpu);
bool i0B_DEC_BC(CPU* cpu);

bool i13_INC_DE(CPU* cpu);
bool i19_ADD_HL_DE(CPU* cpu);
bool i1B_DEC_DE(CPU* cpu);

bool i23_INC_HL(CPU* cpu); // INC HL
bool i29_ADD_HL_HL(CPU* cpu);
bool i2B_DEC_HL(CPU* cpu);

bool i39_ADD_HL_SP(CPU* cpu);
bool i3B_DEC_SP(CPU* cpu);

#endif
