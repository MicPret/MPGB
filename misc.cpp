#include <mpgb/instr/misc.h>
#include <mpgb/CPU.h>


bool i27_DAA(CPU* cpu) {
    std::uint8_t adj = 0;
    if (cpu->FlagSubtract()) {
        adj += cpu->FlagHalfCarry() * 0x06;
        adj += cpu->FlagCarry() * 0x60;
        cpu->A -= adj;
    } else {
        if (cpu->FlagHalfCarry() || ((cpu->A & 0x0F) > 0x09)) {
            adj += 0x06;
        }
        if (cpu->FlagCarry() || (cpu->A > 0x99)) {
            adj += 0x60;
            cpu->SetFlagCarry(true);
        }
        cpu->A += adj;
    }
    cpu->SetFlagZero(cpu->A == 0);
    cpu->SetFlagHalfCarry(false);
    return true;
}
