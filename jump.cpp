#include "jump.h"
#include "CPU.h"
#include "utils.h"

static bool JR_cc_e8(CPU* cpu, bool cc) {
    auto offset = static_cast<std::int8_t>(cpu->Fetch8());
    if (!cc)
        return false;
    auto address = static_cast<std::int32_t>(cpu->PC) + offset;
    cpu->PC = static_cast<std::uint16_t>(address);
    return true;
}
static bool CALL_cc_a16(CPU* cpu, bool cc);
static bool RET_cc(CPU* cpu, bool cc);
static bool JP_r16(CPU* cpu, std::uint16_t r16);
static bool JP_cc_a16(CPU* cpu, bool cc);
static bool RST(CPU* cpu, std::uint16_t address);

bool i18_JR_e8(CPU* cpu) {
    return JR_cc_e8(cpu, true);
}
bool i20_JR_NZ_e8(CPU* cpu) {
    return JR_cc_e8(cpu, cpu->FlagZero() == 0);
}
bool i28_JR_Z_e8(CPU* cpu) {
    return JR_cc_e8(cpu, cpu->FlagZero() != 0);
}
bool i30_JR_NC_e8(CPU* cpu) {
    return JR_cc_e8(cpu, cpu->FlagCarry() == 0);
}
bool i38_JR_C_e8(CPU* cpu) {
    return JR_cc_e8(cpu, cpu->FlagCarry() != 0);
}

bool iC3_JP_n16(CPU* cpu) {
    auto address = cpu->Fetch16();
    cpu->PC = address;
    return true;
}

bool iCD_CALL_a16(CPU* cpu) {
    return CALL_cc_a16(cpu, true);
}
bool iC4_CALL_NZ_a16(CPU* cpu) {
    return CALL_cc_a16(cpu, cpu->FlagZero() == 0);
}
bool iCC_CALL_Z_a16(CPU* cpu) {
    return CALL_cc_a16(cpu, cpu->FlagZero() != 0);
}
bool iD4_CALL_NC_a16(CPU* cpu) {
    return CALL_cc_a16(cpu, cpu->FlagCarry() == 0);
}
bool iDC_CALL_C_a16(CPU* cpu) {
    return CALL_cc_a16(cpu, cpu->FlagCarry() != 0);
}

bool iC9_RET(CPU* cpu) {
    return RET_cc(cpu, true);
}
bool iC0_RET_NZ(CPU* cpu) {
    return RET_cc(cpu, cpu->FlagZero() == 0);
}
bool iC8_RET_Z(CPU* cpu) {
    return RET_cc(cpu, cpu->FlagZero() != 0);
}
bool iD0_RET_NC(CPU* cpu) {
    return RET_cc(cpu, cpu->FlagCarry() == 0);
}
bool iD8_RET_C(CPU* cpu) {
    return RET_cc(cpu, cpu->FlagCarry() != 0);
}

bool iD9_RETI(CPU* cpu) {
    cpu->SetIME(true);
    return RET_cc(cpu, true);
}

bool iE9_JP_HL(CPU* cpu) {
    return JP_r16(cpu, cpu->HL());
}
bool iC2_JP_NZ_a16(CPU* cpu) {
    return JP_cc_a16(cpu, cpu->FlagZero() == 0);
}
bool iCA_JP_Z_a16(CPU* cpu) {
    return JP_cc_a16(cpu, cpu->FlagZero() != 0);
}
bool iD2_JP_NC_a16(CPU* cpu) {
    return JP_cc_a16(cpu, cpu->FlagCarry() == 0);
}
bool iDA_JP_C_a16(CPU* cpu) {
    return JP_cc_a16(cpu, cpu->FlagCarry() != 0);
}

bool iC7_RST_00(CPU* cpu) {
    return RST(cpu, 0x00);
}
bool iCF_RST_08(CPU* cpu) {
    return RST(cpu, 0x08);
}
bool iD7_RST_10(CPU* cpu) {
    return RST(cpu, 0x10);
}
bool iDF_RST_18(CPU* cpu) {
    return RST(cpu, 0x18);
}
bool iE7_RST_20(CPU* cpu) {
    return RST(cpu, 0x20);
}
bool iEF_RST_28(CPU* cpu) {
    return RST(cpu, 0x28);
}
bool iF7_RST_30(CPU* cpu) {
    return RST(cpu, 0x30);
}
bool iFF_RST_38(CPU* cpu) {
    return RST(cpu, 0x38);
}

bool CALL_cc_a16(CPU* cpu, bool cc) {
    auto address = cpu->Fetch16();
    if (!cc) {
        return false;
    }
    cpu->StackPush16(cpu->PC);
    cpu->PC = address;
    return true;
}
bool RET_cc(CPU* cpu, bool cc) {
    if (!cc) {
        return false;
    }
    cpu->PC = cpu->StackPop16();
    return true;
}
bool JP_r16(CPU* cpu, std::uint16_t r16) {
    cpu->PC = r16;
    return true;
}
bool JP_cc_a16(CPU* cpu, bool cc) {
    auto address = cpu->Fetch16();
    if (!cc) {
        return false;
    }
    cpu->PC = address;
    return true;
}
bool RST(CPU* cpu, std::uint16_t address) {
    cpu->StackPush16(cpu->PC);
    cpu->PC = address;
    return true;
}
