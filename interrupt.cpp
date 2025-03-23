#include <mpgb/instr/interrupt.h>
#include <mpgb/CPU.h>

bool i76_HALT(CPU* cpu) {
    cpu->Halt = true;
    return true;
}

bool iF3_DI(CPU* cpu) {
    cpu->SetIME(false);
    return true;
}

bool iFB_EI(CPU* cpu) {
    cpu->SetIMENext();
    return true;
}
