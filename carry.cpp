#include <mpgb/instr/carry.h>
#include <mpgb/CPU.h>

bool i37_SCF(CPU* cpu) {
    cpu->SetFlagSubtract(false);
    cpu->SetFlagHalfCarry(false);
    cpu->SetFlagCarry(true);
    return true;
}

bool i3F_CCF(CPU* cpu) {
    cpu->SetFlagSubtract(false);
    cpu->SetFlagHalfCarry(false);
    cpu->SetFlagCarry(!cpu->FlagCarry());
    return true;
}
