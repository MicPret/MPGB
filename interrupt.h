#ifndef MPGB_INTERRUPT_H
#define MPGB_INTERRUPT_H

class CPU;

bool i76_HALT(CPU* cpu);

bool iF3_DI(CPU* cpu);
bool iFB_EI(CPU* cpu);

#endif
