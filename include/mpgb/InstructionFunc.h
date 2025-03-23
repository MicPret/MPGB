#ifndef MPGB_INSTRUCTION_FUNC_H
#define MPGB_INSTRUCTION_FUNC_H

#include <array>

class CPU;

using InstructionFunc = bool (*)(CPU*);

const std::array<InstructionFunc, 512>& GetInstructionFuncTable();

#endif
