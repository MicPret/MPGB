#include "stack.h"
#include "CPU.h"
#include "utils.h"

static bool PUSH_r16(CPU* cpu, std::uint8_t hi, std::uint8_t lo);
static bool POP_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo);

bool i08_LD_a16_SP(CPU* cpu) {
    auto address = cpu->Fetch16();
    auto bus = cpu->GetBus();
    std::uint8_t hi, lo;
    to_r8(cpu->SP, &hi, &lo);
    bus->Write8(address, lo);
    bus->Write8(address + 1, hi);
    return true;
}
bool i31_LD_SP_n16(CPU* cpu) {
    cpu->SP = cpu->Fetch16();
    return true;
}
bool iF9_LD_SP_HL(CPU* cpu) {
    cpu->SP = cpu->HL();
    return true;
}

bool iF8_LD_HL_SP_e8(CPU* cpu) {
    auto unsign = cpu->Fetch8();
    unsigned lo = cpu->SP & 0xFF;
    auto half = (unsign & 0xF) + (lo & 0xF);
    auto result_unsign = lo + unsign;
    cpu->SetFlags(false, false, half > 0xF, result_unsign > 0xFF);
    auto sign = static_cast<std::int8_t>(unsign);
    auto result = static_cast<std::uint16_t>(cpu->SP + sign);
    cpu->SetHL(result);
    return true;
}

bool iC5_PUSH_BC(CPU* cpu) {
    return PUSH_r16(cpu, cpu->B, cpu->C);
}
bool iD5_PUSH_DE(CPU* cpu) {
    return PUSH_r16(cpu, cpu->D, cpu->E);
}
bool iE5_PUSH_HL(CPU* cpu) {
    return PUSH_r16(cpu, cpu->H, cpu->L);
}
bool iF5_PUSH_AF(CPU* cpu) {
    return PUSH_r16(cpu, cpu->A, cpu->F);
}

bool iC1_POP_BC(CPU* cpu) {
    return POP_r16(cpu, &cpu->B, &cpu->C);
}
bool iD1_POP_DE(CPU* cpu) {
    return POP_r16(cpu, &cpu->D, &cpu->E);
}
bool iE1_POP_HL(CPU* cpu) {
    return POP_r16(cpu, &cpu->H, &cpu->L);
}
bool iF1_POP_AF(CPU* cpu) {
    POP_r16(cpu, &cpu->A, &cpu->F);
    cpu->F &= 0xF0;
    return true;
}

bool i33_INC_SP(CPU* cpu) {
    cpu->SP++;
    return true;
}
bool iE8_ADD_SP_e8(CPU* cpu) {
    auto unsign = cpu->Fetch8();
    unsigned lo = cpu->SP & 0xFF;
    unsigned half = (lo & 0xF) + (unsign & 0xF);
    unsigned result_unsign = lo + unsign;
    cpu->SetFlags(false, false, half > 0xF, result_unsign > 0xFF);
    auto sign = static_cast<std::int8_t>(unsign);
    cpu->SP = static_cast<std::uint16_t>(cpu->SP + sign);
    return true;
}



bool PUSH_r16(CPU* cpu, std::uint8_t hi, std::uint8_t lo) {
    cpu->StackPush16(hi, lo);
    return true;
}
bool POP_r16(CPU* cpu, std::uint8_t* hi, std::uint8_t* lo) {
    auto value = cpu->StackPop16();
    to_r8(value, hi, lo);
    return true;
}

