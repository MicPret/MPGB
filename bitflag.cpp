#include <mpgb/instr/bitflag.h>
#include <mpgb/CPU.h>

static bool BIT_u3_r8(CPU* cpu, std::uint8_t u3, std::uint8_t r8);
static bool BIT_u3_HL(CPU* cpu, std::uint8_t u3);
static bool RES_u3_r8(std::uint8_t u3, std::uint8_t* r8);
static bool RES_u3_HL(CPU* cpu, std::uint8_t u3);
static bool SET_u3_r8(std::uint8_t u3, std::uint8_t* r8);
static bool SET_u3_HL(CPU* cpu, std::uint8_t u3);

// BIT u3,r8 (/ [HL])
bool iCB40_BIT_0_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->B);
}
bool iCB41_BIT_0_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->C);
}
bool iCB42_BIT_0_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->D);
}
bool iCB43_BIT_0_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->E);
}
bool iCB44_BIT_0_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->H);
}
bool iCB45_BIT_0_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->L);
}
bool iCB46_BIT_0_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 0);
}
bool iCB47_BIT_0_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 0, cpu->A);
}
bool iCB48_BIT_1_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->B);
}
bool iCB49_BIT_1_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->C);
}
bool iCB4A_BIT_1_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->D);
}
bool iCB4B_BIT_1_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->E);
}
bool iCB4C_BIT_1_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->H);
}
bool iCB4D_BIT_1_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->L);
}
bool iCB4E_BIT_1_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 1);
}
bool iCB4F_BIT_1_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 1, cpu->A);
}
bool iCB50_BIT_2_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->B);
}
bool iCB51_BIT_2_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->C);
}
bool iCB52_BIT_2_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->D);
}
bool iCB53_BIT_2_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->E);
}
bool iCB54_BIT_2_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->H);
}
bool iCB55_BIT_2_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->L);
}
bool iCB56_BIT_2_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 2);
}
bool iCB57_BIT_2_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 2, cpu->A);
}
bool iCB58_BIT_3_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->B);
}
bool iCB59_BIT_3_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->C);
}
bool iCB5A_BIT_3_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->D);
}
bool iCB5B_BIT_3_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->E);
}
bool iCB5C_BIT_3_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->H);
}
bool iCB5D_BIT_3_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->L);
}
bool iCB5E_BIT_3_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 3);
}
bool iCB5F_BIT_3_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 3, cpu->A);
}
bool iCB60_BIT_4_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->B);
}
bool iCB61_BIT_4_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->C);
}
bool iCB62_BIT_4_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->D);
}
bool iCB63_BIT_4_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->E);
}
bool iCB64_BIT_4_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->H);
}
bool iCB65_BIT_4_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->L);
}
bool iCB66_BIT_4_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 4);
}
bool iCB67_BIT_4_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 4, cpu->A);
}
bool iCB68_BIT_5_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->B);
}
bool iCB69_BIT_5_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->C);
}
bool iCB6A_BIT_5_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->D);
}
bool iCB6B_BIT_5_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->E);
}
bool iCB6C_BIT_5_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->H);
}
bool iCB6D_BIT_5_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->L);
}
bool iCB6E_BIT_5_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 5);
}
bool iCB6F_BIT_5_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 5, cpu->A);
}
bool iCB70_BIT_6_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->B);
}
bool iCB71_BIT_6_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->C);
}
bool iCB72_BIT_6_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->D);
}
bool iCB73_BIT_6_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->E);
}
bool iCB74_BIT_6_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->H);
}
bool iCB75_BIT_6_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->L);
}
bool iCB76_BIT_6_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 6);
}
bool iCB77_BIT_6_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 6, cpu->A);
}
bool iCB78_BIT_7_B(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->B);
}
bool iCB79_BIT_7_C(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->C);
}
bool iCB7A_BIT_7_D(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->D);
}
bool iCB7B_BIT_7_E(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->E);
}
bool iCB7C_BIT_7_H(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->H);
}
bool iCB7D_BIT_7_L(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->L);
}
bool iCB7E_BIT_7_HL(CPU* cpu) {
    return BIT_u3_HL(cpu, 7);
}
bool iCB7F_BIT_7_A(CPU* cpu) {
    return BIT_u3_r8(cpu, 7, cpu->A);
}

// RES u3,r8 (/ [HL])
bool iCB80_RES_0_B(CPU* cpu) {
    return RES_u3_r8(0, &cpu->B);
}
bool iCB81_RES_0_C(CPU* cpu) {
    return RES_u3_r8(0, &cpu->C);
}
bool iCB82_RES_0_D(CPU* cpu) {
    return RES_u3_r8(0, &cpu->D);
}
bool iCB83_RES_0_E(CPU* cpu) {
    return RES_u3_r8(0, &cpu->E);
}
bool iCB84_RES_0_H(CPU* cpu) {
    return RES_u3_r8(0, &cpu->H);
}
bool iCB85_RES_0_L(CPU* cpu) {
    return RES_u3_r8(0, &cpu->L);
}
bool iCB86_RES_0_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 0);
}
bool iCB87_RES_0_A(CPU* cpu) {
    return RES_u3_r8(0, &cpu->A);
}
bool iCB88_RES_1_B(CPU* cpu) {
    return RES_u3_r8(1, &cpu->B);
}
bool iCB89_RES_1_C(CPU* cpu) {
    return RES_u3_r8(1, &cpu->C);
}
bool iCB8A_RES_1_D(CPU* cpu) {
    return RES_u3_r8(1, &cpu->D);
}
bool iCB8B_RES_1_E(CPU* cpu) {
    return RES_u3_r8(1, &cpu->E);
}
bool iCB8C_RES_1_H(CPU* cpu) {
    return RES_u3_r8(1, &cpu->H);
}
bool iCB8D_RES_1_L(CPU* cpu) {
    return RES_u3_r8(1, &cpu->L);
}
bool iCB8E_RES_1_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 1);
}
bool iCB8F_RES_1_A(CPU* cpu) {
    return RES_u3_r8(1, &cpu->A);
}
bool iCB90_RES_2_B(CPU* cpu) {
    return RES_u3_r8(2, &cpu->B);
}
bool iCB91_RES_2_C(CPU* cpu) {
    return RES_u3_r8(2, &cpu->C);
}
bool iCB92_RES_2_D(CPU* cpu) {
    return RES_u3_r8(2, &cpu->D);
}
bool iCB93_RES_2_E(CPU* cpu) {
    return RES_u3_r8(2, &cpu->E);
}
bool iCB94_RES_2_H(CPU* cpu) {
    return RES_u3_r8(2, &cpu->H);
}
bool iCB95_RES_2_L(CPU* cpu) {
    return RES_u3_r8(2, &cpu->L);
}
bool iCB96_RES_2_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 2);
}
bool iCB97_RES_2_A(CPU* cpu) {
    return RES_u3_r8(2, &cpu->A);
}
bool iCB98_RES_3_B(CPU* cpu) {
    return RES_u3_r8(3, &cpu->B);
}
bool iCB99_RES_3_C(CPU* cpu) {
    return RES_u3_r8(3, &cpu->C);
}
bool iCB9A_RES_3_D(CPU* cpu) {
    return RES_u3_r8(3, &cpu->D);
}
bool iCB9B_RES_3_E(CPU* cpu) {
    return RES_u3_r8(3, &cpu->E);
}
bool iCB9C_RES_3_H(CPU* cpu) {
    return RES_u3_r8(3, &cpu->H);
}
bool iCB9D_RES_3_L(CPU* cpu) {
    return RES_u3_r8(3, &cpu->L);
}
bool iCB9E_RES_3_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 3);
}
bool iCB9F_RES_3_A(CPU* cpu) {
    return RES_u3_r8(3, &cpu->A);
}
bool iCBA0_RES_4_B(CPU* cpu) {
    return RES_u3_r8(4, &cpu->B);
}
bool iCBA1_RES_4_C(CPU* cpu) {
    return RES_u3_r8(4, &cpu->C);
}
bool iCBA2_RES_4_D(CPU* cpu) {
    return RES_u3_r8(4, &cpu->D);
}
bool iCBA3_RES_4_E(CPU* cpu) {
    return RES_u3_r8(4, &cpu->E);
}
bool iCBA4_RES_4_H(CPU* cpu) {
    return RES_u3_r8(4, &cpu->H);
}
bool iCBA5_RES_4_L(CPU* cpu) {
    return RES_u3_r8(4, &cpu->L);
}
bool iCBA6_RES_4_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 4);
}
bool iCBA7_RES_4_A(CPU* cpu) {
    return RES_u3_r8(4, &cpu->A);
}
bool iCBA8_RES_5_B(CPU* cpu) {
    return RES_u3_r8(5, &cpu->B);
}
bool iCBA9_RES_5_C(CPU* cpu) {
    return RES_u3_r8(5, &cpu->C);
}
bool iCBAA_RES_5_D(CPU* cpu) {
    return RES_u3_r8(5, &cpu->D);
}
bool iCBAB_RES_5_E(CPU* cpu) {
    return RES_u3_r8(5, &cpu->E);
}
bool iCBAC_RES_5_H(CPU* cpu) {
    return RES_u3_r8(5, &cpu->H);
}
bool iCBAD_RES_5_L(CPU* cpu) {
    return RES_u3_r8(5, &cpu->L);
}
bool iCBAE_RES_5_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 5);
}
bool iCBAF_RES_5_A(CPU* cpu) {
    return RES_u3_r8(5, &cpu->A);
}
bool iCBB0_RES_6_B(CPU* cpu) {
    return RES_u3_r8(6, &cpu->B);
}
bool iCBB1_RES_6_C(CPU* cpu) {
    return RES_u3_r8(6, &cpu->C);
}
bool iCBB2_RES_6_D(CPU* cpu) {
    return RES_u3_r8(6, &cpu->D);
}
bool iCBB3_RES_6_E(CPU* cpu) {
    return RES_u3_r8(6, &cpu->E);
}
bool iCBB4_RES_6_H(CPU* cpu) {
    return RES_u3_r8(6, &cpu->H);
}
bool iCBB5_RES_6_L(CPU* cpu) {
    return RES_u3_r8(6, &cpu->L);
}
bool iCBB6_RES_6_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 6);
}
bool iCBB7_RES_6_A(CPU* cpu) {
    return RES_u3_r8(6, &cpu->A);
}
bool iCBB8_RES_7_B(CPU* cpu) {
    return RES_u3_r8(7, &cpu->B);
}
bool iCBB9_RES_7_C(CPU* cpu) {
    return RES_u3_r8(7, &cpu->C);
}
bool iCBBA_RES_7_D(CPU* cpu) {
    return RES_u3_r8(7, &cpu->D);
}
bool iCBBB_RES_7_E(CPU* cpu) {
    return RES_u3_r8(7, &cpu->E);
}
bool iCBBC_RES_7_H(CPU* cpu) {
    return RES_u3_r8(7, &cpu->H);
}
bool iCBBD_RES_7_L(CPU* cpu) {
    return RES_u3_r8(7, &cpu->L);
}
bool iCBBE_RES_7_HL(CPU* cpu) {
    return RES_u3_HL(cpu, 7);
}
bool iCBBF_RES_7_A(CPU* cpu) {
    return RES_u3_r8(7, &cpu->A);
}

// SET u3,r8 (/ [HL])
bool iCBC0_SET_0_B(CPU* cpu) {
    return SET_u3_r8(0, &cpu->B);
}
bool iCBC1_SET_0_C(CPU* cpu) {
    return SET_u3_r8(0, &cpu->C);
}
bool iCBC2_SET_0_D(CPU* cpu) {
    return SET_u3_r8(0, &cpu->D);
}
bool iCBC3_SET_0_E(CPU* cpu) {
    return SET_u3_r8(0, &cpu->E);
}
bool iCBC4_SET_0_H(CPU* cpu) {
    return SET_u3_r8(0, &cpu->H);
}
bool iCBC5_SET_0_L(CPU* cpu) {
    return SET_u3_r8(0, &cpu->L);
}
bool iCBC6_SET_0_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 0);
}
bool iCBC7_SET_0_A(CPU* cpu) {
    return SET_u3_r8(0, &cpu->A);
}
bool iCBC8_SET_1_B(CPU* cpu) {
    return SET_u3_r8(1, &cpu->B);
}
bool iCBC9_SET_1_C(CPU* cpu) {
    return SET_u3_r8(1, &cpu->C);
}
bool iCBCA_SET_1_D(CPU* cpu) {
    return SET_u3_r8(1, &cpu->D);
}
bool iCBCB_SET_1_E(CPU* cpu) {
    return SET_u3_r8(1, &cpu->E);
}
bool iCBCC_SET_1_H(CPU* cpu) {
    return SET_u3_r8(1, &cpu->H);
}
bool iCBCD_SET_1_L(CPU* cpu) {
    return SET_u3_r8(1, &cpu->L);
}
bool iCBCE_SET_1_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 1);
}
bool iCBCF_SET_1_A(CPU* cpu) {
    return SET_u3_r8(1, &cpu->A);
}
bool iCBD0_SET_2_B(CPU* cpu) {
    return SET_u3_r8(2, &cpu->B);
}
bool iCBD1_SET_2_C(CPU* cpu) {
    return SET_u3_r8(2, &cpu->C);
}
bool iCBD2_SET_2_D(CPU* cpu) {
    return SET_u3_r8(2, &cpu->D);
}
bool iCBD3_SET_2_E(CPU* cpu) {
    return SET_u3_r8(2, &cpu->E);
}
bool iCBD4_SET_2_H(CPU* cpu) {
    return SET_u3_r8(2, &cpu->H);
}
bool iCBD5_SET_2_L(CPU* cpu) {
    return SET_u3_r8(2, &cpu->L);
}
bool iCBD6_SET_2_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 2);
}
bool iCBD7_SET_2_A(CPU* cpu) {
    return SET_u3_r8(2, &cpu->A);
}
bool iCBD8_SET_3_B(CPU* cpu) {
    return SET_u3_r8(3, &cpu->B);
}
bool iCBD9_SET_3_C(CPU* cpu) {
    return SET_u3_r8(3, &cpu->C);
}
bool iCBDA_SET_3_D(CPU* cpu) {
    return SET_u3_r8(3, &cpu->D);
}
bool iCBDB_SET_3_E(CPU* cpu) {
    return SET_u3_r8(3, &cpu->E);
}
bool iCBDC_SET_3_H(CPU* cpu) {
    return SET_u3_r8(3, &cpu->H);
}
bool iCBDD_SET_3_L(CPU* cpu) {
    return SET_u3_r8(3, &cpu->L);
}
bool iCBDE_SET_3_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 3);
}
bool iCBDF_SET_3_A(CPU* cpu) {
    return SET_u3_r8(3, &cpu->A);
}
bool iCBE0_SET_4_B(CPU* cpu) {
    return SET_u3_r8(4, &cpu->B);
}
bool iCBE1_SET_4_C(CPU* cpu) {
    return SET_u3_r8(4, &cpu->C);
}
bool iCBE2_SET_4_D(CPU* cpu) {
    return SET_u3_r8(4, &cpu->D);
}
bool iCBE3_SET_4_E(CPU* cpu) {
    return SET_u3_r8(4, &cpu->E);
}
bool iCBE4_SET_4_H(CPU* cpu) {
    return SET_u3_r8(4, &cpu->H);
}
bool iCBE5_SET_4_L(CPU* cpu) {
    return SET_u3_r8(4, &cpu->L);
}
bool iCBE6_SET_4_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 4);
}
bool iCBE7_SET_4_A(CPU* cpu) {
    return SET_u3_r8(4, &cpu->A);
}
bool iCBE8_SET_5_B(CPU* cpu) {
    return SET_u3_r8(5, &cpu->B);
}
bool iCBE9_SET_5_C(CPU* cpu) {
    return SET_u3_r8(5, &cpu->C);
}
bool iCBEA_SET_5_D(CPU* cpu) {
    return SET_u3_r8(5, &cpu->D);
}
bool iCBEB_SET_5_E(CPU* cpu) {
    return SET_u3_r8(5, &cpu->E);
}
bool iCBEC_SET_5_H(CPU* cpu) {
    return SET_u3_r8(5, &cpu->H);
}
bool iCBED_SET_5_L(CPU* cpu) {
    return SET_u3_r8(5, &cpu->L);
}
bool iCBEE_SET_5_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 5);
}
bool iCBEF_SET_5_A(CPU* cpu) {
    return SET_u3_r8(5, &cpu->A);
}
bool iCBF0_SET_6_B(CPU* cpu) {
    return SET_u3_r8(6, &cpu->B);
}
bool iCBF1_SET_6_C(CPU* cpu) {
    return SET_u3_r8(6, &cpu->C);
}
bool iCBF2_SET_6_D(CPU* cpu) {
    return SET_u3_r8(6, &cpu->D);
}
bool iCBF3_SET_6_E(CPU* cpu) {
    return SET_u3_r8(6, &cpu->E);
}
bool iCBF4_SET_6_H(CPU* cpu) {
    return SET_u3_r8(6, &cpu->H);
}
bool iCBF5_SET_6_L(CPU* cpu) {
    return SET_u3_r8(6, &cpu->L);
}
bool iCBF6_SET_6_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 6);
}
bool iCBF7_SET_6_A(CPU* cpu) {
    return SET_u3_r8(6, &cpu->A);
}
bool iCBF8_SET_7_B(CPU* cpu) {
    return SET_u3_r8(7, &cpu->B);
}
bool iCBF9_SET_7_C(CPU* cpu) {
    return SET_u3_r8(7, &cpu->C);
}
bool iCBFA_SET_7_D(CPU* cpu) {
    return SET_u3_r8(7, &cpu->D);
}
bool iCBFB_SET_7_E(CPU* cpu) {
    return SET_u3_r8(7, &cpu->E);
}
bool iCBFC_SET_7_H(CPU* cpu) {
    return SET_u3_r8(7, &cpu->H);
}
bool iCBFD_SET_7_L(CPU* cpu) {
    return SET_u3_r8(7, &cpu->L);
}
bool iCBFE_SET_7_HL(CPU* cpu) {
    return SET_u3_HL(cpu, 7);
}
bool iCBFF_SET_7_A(CPU* cpu) {
    return SET_u3_r8(7, &cpu->A);
}


bool BIT_u3_r8(CPU* cpu, std::uint8_t u3, std::uint8_t r8) {
    auto bit = (r8 >> u3) & 1;
    cpu->SetFlagZero(bit == 0);
    cpu->SetFlagSubtract(false);
    cpu->SetFlagHalfCarry(true);
    return true;
}
bool BIT_u3_HL(CPU* cpu, std::uint8_t u3) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    return BIT_u3_r8(cpu, u3, value);
}
bool RES_u3_r8(std::uint8_t u3, std::uint8_t* r8) {
    *r8 = *r8 & ~(1 << u3);
    return true;
}
bool RES_u3_HL(CPU* cpu, std::uint8_t u3) {
    auto address = cpu->HL();
    auto bus = cpu->GetBus();
    auto value = bus->Read8(address);
    RES_u3_r8(u3, &value);
    bus->Write8(address, value);
    return true;
}
bool SET_u3_r8(std::uint8_t u3, std::uint8_t* r8) {
    *r8 = *r8 | (1 << u3);
    return true;
}
bool SET_u3_HL(CPU* cpu, std::uint8_t u3) {
    auto address = cpu->HL();
    auto bus = cpu->GetBus();
    auto value = bus->Read8(address);
    SET_u3_r8(u3, &value);
    bus->Write8(address, value);
    return true;
}
