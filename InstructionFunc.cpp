#include <mpgb/InstructionFunc.h>

#include <mpgb/instr/arithmetic8.h>
#include <mpgb/instr/arithmetic16.h>
#include <mpgb/instr/bitflag.h>
#include <mpgb/instr/bitwise.h>
#include <mpgb/instr/bitshift.h>
#include <mpgb/instr/carry.h>
#include <mpgb/instr/interrupt.h>
#include <mpgb/instr/jump.h>
#include <mpgb/instr/load.h>
#include <mpgb/instr/misc.h>
#include <mpgb/instr/stack.h>

constexpr std::array<InstructionFunc, 512> CreateTable() {
    std::array<InstructionFunc, 512> t = { nullptr };
    // 0x
    t[0x00] = [](CPU*) { return true; }; // NOP
    t[0x01] = i01_LD_BC_n16;
    t[0x02] = i02_LD_BC_A;
    t[0x03] = i03_INC_BC;
    t[0x04] = i04_INC_B;
    t[0x05] = i05_DEC_B;
    t[0x06] = i06_LD_B_n8;
    t[0x07] = i07_RLCA;
    t[0x08] = i08_LD_a16_SP;
    t[0x09] = i09_ADD_HL_BC;
    t[0x0A] = i0A_LD_A_BC;
    t[0x0B] = i0B_DEC_BC;
    t[0x0C] = i0C_INC_C;
    t[0x0D] = i0D_DEC_C;
    t[0x0E] = i0E_LD_C_n8;
    t[0x0F] = i0F_RRCA;
    // 1x
    t[0x11] = i11_LD_DE_n16;
    t[0x12] = i12_LD_DE_A;
    t[0x13] = i13_INC_DE;
    t[0x14] = i14_INC_D;
    t[0x15] = i15_DEC_D;
    t[0x16] = i16_LD_D_n8;
    t[0x17] = i17_RLA;
    t[0x18] = i18_JR_e8;
    t[0x19] = i19_ADD_HL_DE;
    t[0x1A] = i1A_LD_A_DE;
    t[0x1B] = i1B_DEC_DE;
    t[0x1C] = i1C_INC_E;
    t[0x1D] = i1D_DEC_E;
    t[0x1E] = i1E_LD_E_n8;
    t[0x1F] = i1F_RRA;
    // 2x
    t[0x20] = i20_JR_NZ_e8;
    t[0x21] = i21_LD_HL_n16;
    t[0x22] = i22_LD_HLI_A;
    t[0x23] = i23_INC_HL;
    t[0x24] = i24_INC_H;
    t[0x25] = i25_DEC_H;
    t[0x26] = i26_LD_H_n8;
    t[0x27] = i27_DAA;
    t[0x28] = i28_JR_Z_e8;
    t[0x29] = i29_ADD_HL_HL;
    t[0x2A] = i2A_LD_A_HLI;
    t[0x2B] = i2B_DEC_HL;
    t[0x2C] = i2C_INC_L;
    t[0x2D] = i2D_DEC_L;
    t[0x2E] = i2E_LD_L_n8;
    t[0x2F] = i2F_CPL;
    // 3x
    t[0x30] = i30_JR_NC_e8;
    t[0x31] = i31_LD_SP_n16;
    t[0x32] = i32_LD_HLD_A;
    t[0x33] = i33_INC_SP;
    t[0x34] = i34_INC_HL;
    t[0x35] = i35_DEC_HL;
    t[0x36] = i36_LD_HL_n8;
    t[0x37] = i37_SCF;
    t[0x38] = i38_JR_C_e8;
    t[0x39] = i39_ADD_HL_SP;
    t[0x3A] = i3A_LD_A_HLD;
    t[0x3B] = i3B_DEC_SP;
    t[0x3C] = i3C_INC_A;
    t[0x3D] = i3D_DEC_A;
    t[0x3E] = i3E_LD_A_n8;
    t[0x3F] = i3F_CCF;
    // 4x
    t[0x40] = i40_LD_B_B;
    t[0x41] = i41_LD_B_C;
    t[0x42] = i42_LD_B_D;
    t[0x43] = i43_LD_B_E;
    t[0x44] = i44_LD_B_H;
    t[0x45] = i45_LD_B_L;
    t[0x46] = i46_LD_B_HL;
    t[0x47] = i47_LD_B_A;
    t[0x48] = i48_LD_C_B;
    t[0x49] = i49_LD_C_C;
    t[0x4A] = i4A_LD_C_D;
    t[0x4B] = i4B_LD_C_E;
    t[0x4C] = i4C_LD_C_H;
    t[0x4D] = i4D_LD_C_L;
    t[0x4E] = i4E_LD_C_HL;
    t[0x4F] = i4F_LD_C_A;
    // 5x
    t[0x50] = i50_LD_D_B;
    t[0x51] = i51_LD_D_C;
    t[0x52] = i52_LD_D_D;
    t[0x53] = i53_LD_D_E;
    t[0x54] = i54_LD_D_H;
    t[0x55] = i55_LD_D_L;
    t[0x56] = i56_LD_D_HL;
    t[0x57] = i57_LD_D_A;
    t[0x58] = i58_LD_E_B;
    t[0x59] = i59_LD_E_C;
    t[0x5A] = i5A_LD_E_D;
    t[0x5B] = i5B_LD_E_E;
    t[0x5C] = i5C_LD_E_H;
    t[0x5D] = i5D_LD_E_L;
    t[0x5E] = i5E_LD_E_HL;
    t[0x5F] = i5F_LD_E_A;
    // 6x
    t[0x60] = i60_LD_H_B;
    t[0x61] = i61_LD_H_C;
    t[0x62] = i62_LD_H_D;
    t[0x63] = i63_LD_H_E;
    t[0x64] = i64_LD_H_H;
    t[0x65] = i65_LD_H_L;
    t[0x66] = i66_LD_H_HL;
    t[0x67] = i67_LD_H_A;
    t[0x68] = i68_LD_L_B;
    t[0x69] = i69_LD_L_C;
    t[0x6A] = i6A_LD_L_D;
    t[0x6B] = i6B_LD_L_E;
    t[0x6C] = i6C_LD_L_H;
    t[0x6D] = i6D_LD_L_L;
    t[0x6E] = i6E_LD_H_HL;
    t[0x6F] = i6F_LD_L_A;
    // 7x
    t[0x70] = i70_LD_HL_B;
    t[0x71] = i71_LD_HL_C;
    t[0x72] = i72_LD_HL_D;
    t[0x73] = i73_LD_HL_E;
    t[0x74] = i74_LD_HL_H;
    t[0x75] = i75_LD_HL_L;
    t[0x76] = i76_HALT;
    t[0x77] = i77_LD_HL_A;
    t[0x78] = i78_LD_A_B;
    t[0x79] = i79_LD_A_C;
    t[0x7A] = i7A_LD_A_D;
    t[0x7B] = i7B_LD_A_E;
    t[0x7C] = i7C_LD_A_H;
    t[0x7D] = i7D_LD_A_L;
    t[0x7E] = i7E_LD_A_HL;
    t[0x7F] = i7F_LD_A_A;
    // 8x
    t[0X80] = i80_ADD_A_B;
    t[0X81] = i81_ADD_A_C;
    t[0X82] = i82_ADD_A_D;
    t[0X83] = i83_ADD_A_E;
    t[0X84] = i84_ADD_A_H;
    t[0X85] = i85_ADD_A_L;
    t[0X86] = i86_ADD_A_HL;
    t[0X87] = i87_ADD_A_A;
    t[0X88] = i88_ADC_A_B;
    t[0X89] = i89_ADC_A_C;
    t[0X8A] = i8A_ADC_A_D;
    t[0X8B] = i8B_ADC_A_E;
    t[0X8C] = i8C_ADC_A_H;
    t[0X8D] = i8D_ADC_A_L;
    t[0X8E] = i8E_ADC_A_HL;
    t[0X8F] = i8F_ADC_A_A;
    // 9x
    t[0x90] = i90_SUB_A_B;
    t[0x91] = i91_SUB_A_C;
    t[0x92] = i92_SUB_A_D;
    t[0x93] = i93_SUB_A_E;
    t[0x94] = i94_SUB_A_H;
    t[0x95] = i95_SUB_A_L;
    t[0x96] = i96_SUB_A_HL;
    t[0x97] = i97_SUB_A_A;
    t[0x98] = i98_SBC_A_B;
    t[0x99] = i99_SBC_A_C;
    t[0x9A] = i9A_SBC_A_D;
    t[0x9B] = i9B_SBC_A_E;
    t[0x9C] = i9C_SBC_A_H;
    t[0x9D] = i9D_SBC_A_L;
    t[0x9E] = i9E_SBC_A_HL;
    t[0x9F] = i9F_SBC_A_A;
    // Ax
    t[0xA0] = iA0_AND_A_B;
    t[0xA1] = iA1_AND_A_C;
    t[0xA2] = iA2_AND_A_D;
    t[0xA3] = iA3_AND_A_E;
    t[0xA4] = iA4_AND_A_H;
    t[0xA5] = iA5_AND_A_L;
    t[0xA6] = iA6_AND_A_HL;
    t[0xA7] = iA7_AND_A_A;
    t[0xA8] = iA8_XOR_A_B;
    t[0xA9] = iA9_XOR_A_C;
    t[0xAA] = iAA_XOR_A_D;
    t[0xAB] = iAB_XOR_A_E;
    t[0xAC] = iAC_XOR_A_H;
    t[0xAD] = iAD_XOR_A_L;
    t[0xAE] = iAE_XOR_A_HL;
    t[0xAF] = iAF_XOR_A_A;
    // Bx
    t[0xB0] = iB0_OR_A_B;
    t[0xB1] = iB1_OR_A_C;
    t[0xB2] = iB2_OR_A_D;
    t[0xB3] = iB3_OR_A_E;
    t[0xB4] = iB4_OR_A_H;
    t[0xB5] = iB5_OR_A_L;
    t[0xB6] = iB6_OR_A_HL;
    t[0xB7] = iB7_OR_A_A;
    t[0xB8] = iB8_CP_A_B;
    t[0xB9] = iB9_CP_A_C;
    t[0xBA] = iBA_CP_A_D;
    t[0xBB] = iBB_CP_A_E;
    t[0xBC] = iBC_CP_A_H;
    t[0xBD] = iBD_CP_A_L;
    t[0xBE] = iBE_CP_A_HL;
    t[0xBF] = iBF_CP_A_A;
    // Cx
    t[0xC0] = iC0_RET_NZ;
    t[0xC1] = iC1_POP_BC;
    t[0xC2] = iC2_JP_NZ_a16;
    t[0xC3] = iC3_JP_n16;
    t[0xC4] = iC4_CALL_NZ_a16;
    t[0xC5] = iC5_PUSH_BC;
    t[0xC6] = iC6_ADD_A_n8;
    t[0xC7] = iC7_RST_00;
    t[0xC8] = iC8_RET_Z;
    t[0xC9] = iC9_RET;
    t[0xCA] = iCA_JP_Z_a16;
    t[0xCB] = nullptr;
    t[0xCC] = iCC_CALL_Z_a16;
    t[0xCD] = iCD_CALL_a16;
    t[0xCE] = iCE_ADC_A_n8;
    t[0xCF] = iCF_RST_08;
    // Dx
    t[0xD0] = iD0_RET_NC;
    t[0xD1] = iD1_POP_DE;
    t[0xD2] = iD2_JP_NC_a16;
    t[0xD4] = iD4_CALL_NC_a16;
    t[0xD5] = iD5_PUSH_DE;
    t[0xD6] = iD6_SUB_A_n8;
    t[0xD7] = iD7_RST_10;
    t[0xD8] = iD8_RET_C;
    t[0xD9] = iD9_RETI;
    t[0xDA] = iDA_JP_C_a16;
    t[0xDC] = iDC_CALL_C_a16;
    t[0xDE] = iDE_SBC_A_n8;
    t[0xDF] = iDF_RST_18;
    // Ex
    t[0xE0] = iE0_LDH_a8_A;
    t[0xE1] = iE1_POP_HL;
    t[0xE2] = iE2_LDH_C_A;
    t[0xE5] = iE5_PUSH_HL;
    t[0xE6] = iE6_AND_A_n8;
    t[0xE7] = iE7_RST_20;
    t[0xE8] = iE8_ADD_SP_e8;
    t[0xE9] = iE9_JP_HL;
    t[0xEA] = iEA_LD_a16_A;
    t[0xEE] = iEE_XOR_A_n8;
    t[0xEF] = iEF_RST_28;
    //Fx
    t[0xF0] = iF0_LDH_A_a8;
    t[0xF1] = iF1_POP_AF;
    t[0xF2] = iF2_LDH_A_C;
    t[0xF3] = iF3_DI;
    t[0xF5] = iF5_PUSH_AF;
    t[0xF6] = iF6_OR_A_n8;
    t[0xF7] = iF7_RST_30;
    t[0xF8] = iF8_LD_HL_SP_e8;
    t[0xF9] = iF9_LD_SP_HL;
    t[0xFA] = iFA_LD_A_a16;
    t[0xFB] = iFB_EI;
    t[0xFE] = iFE_CP_A_n8;
    t[0xFF] = iFF_RST_38;

    // CB 0x
    t[0x100] = iCB00_RLC_B;
    t[0x101] = iCB01_RLC_C;
    t[0x102] = iCB02_RLC_D;
    t[0x103] = iCB03_RLC_E;
    t[0x104] = iCB04_RLC_H;
    t[0x105] = iCB05_RLC_L;
    t[0x106] = iCB06_RLC_HL;
    t[0x107] = iCB07_RLC_A;
    t[0x108] = iCB08_RRC_B;
    t[0x109] = iCB09_RRC_C;
    t[0x10A] = iCB0A_RRC_D;
    t[0x10B] = iCB0B_RRC_E;
    t[0x10C] = iCB0C_RRC_H;
    t[0x10D] = iCB0D_RRC_L;
    t[0x10E] = iCB0E_RRC_HL;
    t[0x10F] = iCB0F_RRC_A;
    // CB 1x
    t[0x110] = iCB10_RL_B;
    t[0x111] = iCB11_RL_C;
    t[0x112] = iCB12_RL_D;
    t[0x113] = iCB13_RL_E;
    t[0x114] = iCB14_RL_H;
    t[0x115] = iCB15_RL_L;
    t[0x116] = iCB16_RL_HL;
    t[0x117] = iCB17_RL_A;
    t[0x118] = iCB18_RR_B;
    t[0x119] = iCB19_RR_C;
    t[0x11A] = iCB1A_RR_D;
    t[0x11B] = iCB1B_RR_E;
    t[0x11C] = iCB1C_RR_H;
    t[0x11D] = iCB1D_RR_L;
    t[0x11E] = iCB1E_RR_HL;
    t[0x11F] = iCB1F_RR_A;
    // CB 2x
    t[0x120] = iCB20_SLA_B;
    t[0x121] = iCB21_SLA_C;
    t[0x122] = iCB22_SLA_D;
    t[0x123] = iCB23_SLA_E;
    t[0x124] = iCB24_SLA_H;
    t[0x125] = iCB25_SLA_L;
    t[0x126] = iCB26_SLA_HL;
    t[0x127] = iCB27_SLA_A;
    t[0x128] = iCB28_SRA_B;
    t[0x129] = iCB29_SRA_C;
    t[0x12A] = iCB2A_SRA_D;
    t[0x12B] = iCB2B_SRA_E;
    t[0x12C] = iCB2C_SRA_H;
    t[0x12D] = iCB2D_SRA_L;
    t[0x12E] = iCB2E_SRA_HL;
    t[0x12F] = iCB2F_SRA_A;
    // CB 3x
    t[0x130] = iCB30_SWAP_B;
    t[0x131] = iCB31_SWAP_C;
    t[0x132] = iCB32_SWAP_D;
    t[0x133] = iCB33_SWAP_E;
    t[0x134] = iCB34_SWAP_H;
    t[0x135] = iCB35_SWAP_L;
    t[0x136] = iCB36_SWAP_HL;
    t[0x137] = iCB37_SWAP_A;
    t[0x138] = iCB38_SRL_B;
    t[0x139] = iCB39_SRL_C;
    t[0x13A] = iCB3A_SRL_D;
    t[0x13B] = iCB3B_SRL_E;
    t[0x13C] = iCB3C_SRL_H;
    t[0x13D] = iCB3D_SRL_L;
    t[0x13E] = iCB3E_SRL_HL;
    t[0x13F] = iCB3F_SRL_A;
    // CB 4x
    t[0x140] = iCB40_BIT_0_B;
    t[0x141] = iCB41_BIT_0_C;
    t[0x142] = iCB42_BIT_0_D;
    t[0x143] = iCB43_BIT_0_E;
    t[0x144] = iCB44_BIT_0_H;
    t[0x145] = iCB45_BIT_0_L;
    t[0x146] = iCB46_BIT_0_HL;
    t[0x147] = iCB47_BIT_0_A;
    t[0x148] = iCB48_BIT_1_B;
    t[0x149] = iCB49_BIT_1_C;
    t[0x14A] = iCB4A_BIT_1_D;
    t[0x14B] = iCB4B_BIT_1_E;
    t[0x14C] = iCB4C_BIT_1_H;
    t[0x14D] = iCB4D_BIT_1_L;
    t[0x14E] = iCB4E_BIT_1_HL;
    t[0x14F] = iCB4F_BIT_1_A;
    // CB 5x
    t[0x150] = iCB50_BIT_2_B;
    t[0x151] = iCB51_BIT_2_C;
    t[0x152] = iCB52_BIT_2_D;
    t[0x153] = iCB53_BIT_2_E;
    t[0x154] = iCB54_BIT_2_H;
    t[0x155] = iCB55_BIT_2_L;
    t[0x156] = iCB56_BIT_2_HL;
    t[0x157] = iCB57_BIT_2_A;
    t[0x158] = iCB58_BIT_3_B;
    t[0x159] = iCB59_BIT_3_C;
    t[0x15A] = iCB5A_BIT_3_D;
    t[0x15B] = iCB5B_BIT_3_E;
    t[0x15C] = iCB5C_BIT_3_H;
    t[0x15D] = iCB5D_BIT_3_L;
    t[0x15E] = iCB5E_BIT_3_HL;
    t[0x15F] = iCB5F_BIT_3_A;
    // CB 6x
    t[0x160] = iCB60_BIT_4_B;
    t[0x161] = iCB61_BIT_4_C;
    t[0x162] = iCB62_BIT_4_D;
    t[0x163] = iCB63_BIT_4_E;
    t[0x164] = iCB64_BIT_4_H;
    t[0x165] = iCB65_BIT_4_L;
    t[0x166] = iCB66_BIT_4_HL;
    t[0x167] = iCB67_BIT_4_A;
    t[0x168] = iCB68_BIT_5_B;
    t[0x169] = iCB69_BIT_5_C;
    t[0x16A] = iCB6A_BIT_5_D;
    t[0x16B] = iCB6B_BIT_5_E;
    t[0x16C] = iCB6C_BIT_5_H;
    t[0x16D] = iCB6D_BIT_5_L;
    t[0x16E] = iCB6E_BIT_5_HL;
    t[0x16F] = iCB6F_BIT_5_A;
    // CB 7x
    t[0x170] = iCB70_BIT_6_B;
    t[0x171] = iCB71_BIT_6_C;
    t[0x172] = iCB72_BIT_6_D;
    t[0x173] = iCB73_BIT_6_E;
    t[0x174] = iCB74_BIT_6_H;
    t[0x175] = iCB75_BIT_6_L;
    t[0x176] = iCB76_BIT_6_HL;
    t[0x177] = iCB77_BIT_6_A;
    t[0x178] = iCB78_BIT_7_B;
    t[0x179] = iCB79_BIT_7_C;
    t[0x17A] = iCB7A_BIT_7_D;
    t[0x17B] = iCB7B_BIT_7_E;
    t[0x17C] = iCB7C_BIT_7_H;
    t[0x17D] = iCB7D_BIT_7_L;
    t[0x17E] = iCB7E_BIT_7_HL;
    t[0x17F] = iCB7F_BIT_7_A;
    // CB 8x
    t[0x180] = iCB80_RES_0_B;
    t[0x181] = iCB81_RES_0_C;
    t[0x182] = iCB82_RES_0_D;
    t[0x183] = iCB83_RES_0_E;
    t[0x184] = iCB84_RES_0_H;
    t[0x185] = iCB85_RES_0_L;
    t[0x186] = iCB86_RES_0_HL;
    t[0x187] = iCB87_RES_0_A;
    t[0x188] = iCB88_RES_1_B;
    t[0x189] = iCB89_RES_1_C;
    t[0x18A] = iCB8A_RES_1_D;
    t[0x18B] = iCB8B_RES_1_E;
    t[0x18C] = iCB8C_RES_1_H;
    t[0x18D] = iCB8D_RES_1_L;
    t[0x18E] = iCB8E_RES_1_HL;
    t[0x18F] = iCB8F_RES_1_A;
    // CB 9x
    t[0x190] = iCB90_RES_2_B;
    t[0x191] = iCB91_RES_2_C;
    t[0x192] = iCB92_RES_2_D;
    t[0x193] = iCB93_RES_2_E;
    t[0x194] = iCB94_RES_2_H;
    t[0x195] = iCB95_RES_2_L;
    t[0x196] = iCB96_RES_2_HL;
    t[0x197] = iCB97_RES_2_A;
    t[0x198] = iCB98_RES_3_B;
    t[0x199] = iCB99_RES_3_C;
    t[0x19A] = iCB9A_RES_3_D;
    t[0x19B] = iCB9B_RES_3_E;
    t[0x19C] = iCB9C_RES_3_H;
    t[0x19D] = iCB9D_RES_3_L;
    t[0x19E] = iCB9E_RES_3_HL;
    t[0x19F] = iCB9F_RES_3_A;
    // CB Ax
    t[0x1A0] = iCBA0_RES_4_B;
    t[0x1A1] = iCBA1_RES_4_C;
    t[0x1A2] = iCBA2_RES_4_D;
    t[0x1A3] = iCBA3_RES_4_E;
    t[0x1A4] = iCBA4_RES_4_H;
    t[0x1A5] = iCBA5_RES_4_L;
    t[0x1A6] = iCBA6_RES_4_HL;
    t[0x1A7] = iCBA7_RES_4_A;
    t[0x1A8] = iCBA8_RES_5_B;
    t[0x1A9] = iCBA9_RES_5_C;
    t[0x1AA] = iCBAA_RES_5_D;
    t[0x1AB] = iCBAB_RES_5_E;
    t[0x1AC] = iCBAC_RES_5_H;
    t[0x1AD] = iCBAD_RES_5_L;
    t[0x1AE] = iCBAE_RES_5_HL;
    t[0x1AF] = iCBAF_RES_5_A;
    // CB Bx
    t[0x1B0] = iCBB0_RES_6_B;
    t[0x1B1] = iCBB1_RES_6_C;
    t[0x1B2] = iCBB2_RES_6_D;
    t[0x1B3] = iCBB3_RES_6_E;
    t[0x1B4] = iCBB4_RES_6_H;
    t[0x1B5] = iCBB5_RES_6_L;
    t[0x1B6] = iCBB6_RES_6_HL;
    t[0x1B7] = iCBB7_RES_6_A;
    t[0x1B8] = iCBB8_RES_7_B;
    t[0x1B9] = iCBB9_RES_7_C;
    t[0x1BA] = iCBBA_RES_7_D;
    t[0x1BB] = iCBBB_RES_7_E;
    t[0x1BC] = iCBBC_RES_7_H;
    t[0x1BD] = iCBBD_RES_7_L;
    t[0x1BE] = iCBBE_RES_7_HL;
    t[0x1BF] = iCBBF_RES_7_A;
    // CB Cx
    t[0x1C0] = iCBC0_SET_0_B;
    t[0x1C1] = iCBC1_SET_0_C;
    t[0x1C2] = iCBC2_SET_0_D;
    t[0x1C3] = iCBC3_SET_0_E;
    t[0x1C4] = iCBC4_SET_0_H;
    t[0x1C5] = iCBC5_SET_0_L;
    t[0x1C6] = iCBC6_SET_0_HL;
    t[0x1C7] = iCBC7_SET_0_A;
    t[0x1C8] = iCBC8_SET_1_B;
    t[0x1C9] = iCBC9_SET_1_C;
    t[0x1CA] = iCBCA_SET_1_D;
    t[0x1CB] = iCBCB_SET_1_E;
    t[0x1CC] = iCBCC_SET_1_H;
    t[0x1CD] = iCBCD_SET_1_L;
    t[0x1CE] = iCBCE_SET_1_HL;
    t[0x1CF] = iCBCF_SET_1_A;
    // CB Dx
    t[0x1D0] = iCBD0_SET_2_B;
    t[0x1D1] = iCBD1_SET_2_C;
    t[0x1D2] = iCBD2_SET_2_D;
    t[0x1D3] = iCBD3_SET_2_E;
    t[0x1D4] = iCBD4_SET_2_H;
    t[0x1D5] = iCBD5_SET_2_L;
    t[0x1D6] = iCBD6_SET_2_HL;
    t[0x1D7] = iCBD7_SET_2_A;
    t[0x1D8] = iCBD8_SET_3_B;
    t[0x1D9] = iCBD9_SET_3_C;
    t[0x1DA] = iCBDA_SET_3_D;
    t[0x1DB] = iCBDB_SET_3_E;
    t[0x1DC] = iCBDC_SET_3_H;
    t[0x1DD] = iCBDD_SET_3_L;
    t[0x1DE] = iCBDE_SET_3_HL;
    t[0x1DF] = iCBDF_SET_3_A;
    // CB Ex
    t[0x1E0] = iCBE0_SET_4_B;
    t[0x1E1] = iCBE1_SET_4_C;
    t[0x1E2] = iCBE2_SET_4_D;
    t[0x1E3] = iCBE3_SET_4_E;
    t[0x1E4] = iCBE4_SET_4_H;
    t[0x1E5] = iCBE5_SET_4_L;
    t[0x1E6] = iCBE6_SET_4_HL;
    t[0x1E7] = iCBE7_SET_4_A;
    t[0x1E8] = iCBE8_SET_5_B;
    t[0x1E9] = iCBE9_SET_5_C;
    t[0x1EA] = iCBEA_SET_5_D;
    t[0x1EB] = iCBEB_SET_5_E;
    t[0x1EC] = iCBEC_SET_5_H;
    t[0x1ED] = iCBED_SET_5_L;
    t[0x1EE] = iCBEE_SET_5_HL;
    t[0x1EF] = iCBEF_SET_5_A;
    // CB Fx
    t[0x1F0] = iCBF0_SET_6_B;
    t[0x1F1] = iCBF1_SET_6_C;
    t[0x1F2] = iCBF2_SET_6_D;
    t[0x1F3] = iCBF3_SET_6_E;
    t[0x1F4] = iCBF4_SET_6_H;
    t[0x1F5] = iCBF5_SET_6_L;
    t[0x1F6] = iCBF6_SET_6_HL;
    t[0x1F7] = iCBF7_SET_6_A;
    t[0x1F8] = iCBF8_SET_7_B;
    t[0x1F9] = iCBF9_SET_7_C;
    t[0x1FA] = iCBFA_SET_7_D;
    t[0x1FB] = iCBFB_SET_7_E;
    t[0x1FC] = iCBFC_SET_7_H;
    t[0x1FD] = iCBFD_SET_7_L;
    t[0x1FE] = iCBFE_SET_7_HL;
    t[0x1FF] = iCBFF_SET_7_A;

    return t;
}

const std::array<InstructionFunc, 512>& GetInstructionFuncTable() {
    static constexpr std::array<InstructionFunc, 512> table = CreateTable();
    return table;
}
