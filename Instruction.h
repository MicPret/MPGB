#ifndef MPGB_INSTRUCTION_H
#define MPGB_INSTRUCTION_H

#include "Cycles.h"
#include "InstructionFunc.h"

struct Instruction {
    unsigned opcode;
    InstructionFunc func;
    Cycles cycles;
};

#endif
