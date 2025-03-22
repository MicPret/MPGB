#include "arithmetic8.h"
#include "CPU.h"

static bool CP_A_r8(CPU* cpu, std::uint8_t r8);
static bool SBC_A_r8(CPU* cpu, std::uint8_t r8);
static bool ADC_A_r8(CPU* cpu, std::uint8_t r8) {
    auto carry = cpu->FlagCarry();

    auto result = cpu->A + r8 + carry;
    auto result_8bit = static_cast<std::uint8_t>(result);
    auto half = (cpu->A & 0xF) + (r8 & 0xF) + carry;

    cpu->SetFlags(result_8bit == 0, false, half > 0xF, result > 0xFF);
    cpu->A = result_8bit;

    return true;
}
static bool ADD_A_r8(CPU* cpu, std::uint8_t r8) {
    auto result = cpu->A + r8;
    auto half = (cpu->A & 0xF) + (r8 & 0xF);
    auto result_8bit = static_cast<std::uint8_t>(result);

    cpu->SetFlags(result_8bit == 0, false, half > 0xF, result > 0xFF);
    cpu->A = result_8bit;

    return true;
}
static bool SUB_A_r8(CPU* cpu, std::uint8_t r8) {
    auto result = cpu->A - r8;
    auto result_8bit = static_cast<std::uint8_t>(result);
    cpu->SetFlags(result_8bit == 0, true, (r8 & 0xF) > (cpu->A & 0xF), r8 > cpu->A);
    cpu->A = result_8bit;
    return true;
}
static bool INC_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    auto result = static_cast<std::uint8_t>(value + 1);
    cpu->SetFlagZero(result == 0);
    cpu->SetFlagSubtract(false);
    cpu->SetFlagHalfCarry((result & 0xF) < (value & 0xF));
    *r8 = result;
    return true;
}
static bool DEC_r8(CPU* cpu, std::uint8_t* r8) {
    auto value = *r8;
    auto result = static_cast<std::uint8_t>(value - 1);
    cpu->SetFlagZero(result == 0);
    cpu->SetFlagSubtract(true);
    cpu->SetFlagHalfCarry((result & 0xF) > (value & 0xF));
    *r8 = result;    
    return true;
}

// ADC A,r8
bool i88_ADC_A_B(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->B);
}
bool i89_ADC_A_C(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->C);
}
bool i8A_ADC_A_D(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->D);
}
bool i8B_ADC_A_E(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->E);
}
bool i8C_ADC_A_H(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->H);
}
bool i8D_ADC_A_L(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->L);
}
bool i8F_ADC_A_A(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->A);
}

// ADC A,[HL]
bool i8E_ADC_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    ADC_A_r8(cpu, value);
    return 2;
}

// ADD A,r8
bool i80_ADD_A_B(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->B);
}
bool i81_ADD_A_C(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->C);
}
bool i82_ADD_A_D(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->D);
}
bool i83_ADD_A_E(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->E);
}
bool i84_ADD_A_H(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->H);
}
bool i85_ADD_A_L(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->L);
}
bool i87_ADD_A_A(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->A);
}
// ADD A,n8
bool iC6_ADD_A_n8(CPU* cpu) {
    return ADD_A_r8(cpu, cpu->Fetch8());
}
// ADC A,n8
bool iCE_ADC_A_n8(CPU* cpu) {
    return ADC_A_r8(cpu, cpu->Fetch8());
}
// SUB A,n8
bool iD6_SUB_A_n8(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->Fetch8());
}


// SUB A,r8
bool i90_SUB_A_B(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->B);
}
bool i91_SUB_A_C(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->C);
}
bool i92_SUB_A_D(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->D);
}
bool i93_SUB_A_E(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->E);
}
bool i94_SUB_A_H(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->H);
}
bool i95_SUB_A_L(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->L);
}
bool i97_SUB_A_A(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->A);
}
// SUB A,[HL]
bool i96_SUB_A_HL(CPU* cpu) {
    return SUB_A_r8(cpu, cpu->GetBus()->Read8(cpu->HL()));
}

// ADD A,[HL]
bool i86_ADD_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    return ADD_A_r8(cpu, value);
}

// SBC A,r8
bool i98_SBC_A_B(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->B);
}
bool i99_SBC_A_C(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->C);
}
bool i9A_SBC_A_D(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->D);
}
bool i9B_SBC_A_E(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->E);
}
bool i9C_SBC_A_H(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->H);
}
bool i9D_SBC_A_L(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->L);
}
bool i9F_SBC_A_A(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->A);
}
// SBC A,[HL]
bool i9E_SBC_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    return SBC_A_r8(cpu, value);
}
// SBC A,n8
bool iDE_SBC_A_n8(CPU* cpu) {
    return SBC_A_r8(cpu, cpu->Fetch8());
}

// DEC r8
bool i05_DEC_B(CPU* cpu) {
    return DEC_r8(cpu, &cpu->B);
}
bool i0D_DEC_C(CPU* cpu) {
    return DEC_r8(cpu, &cpu->C);
}
bool i15_DEC_D(CPU* cpu) {
    return DEC_r8(cpu, &cpu->D);
}
bool i1D_DEC_E(CPU* cpu) {
    return DEC_r8(cpu, &cpu->E);
}
bool i25_DEC_H(CPU* cpu) {
    return DEC_r8(cpu, &cpu->H);
}
bool i2D_DEC_L(CPU* cpu) {
    return DEC_r8(cpu, &cpu->L);
}
bool i3D_DEC_A(CPU* cpu) {
    return DEC_r8(cpu, &cpu->A);
}

// INC [HL]
bool i34_INC_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto bus = cpu->GetBus();
    auto value = bus->Read8(address);
    INC_r8(cpu, &value);
    bus->Write8(address, value);
    return true;
}

// DEC [HL]
bool i35_DEC_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto bus = cpu->GetBus();
    auto value = bus->Read8(address);
    DEC_r8(cpu, &value);
    bus->Write8(address, value);
    return true;
}

// INC r8
bool i04_INC_B(CPU* cpu) {
    return INC_r8(cpu, &cpu->B);
}
bool i0C_INC_C(CPU* cpu) {
    return INC_r8(cpu, &cpu->C);
}
bool i14_INC_D(CPU* cpu) {
    return INC_r8(cpu, &cpu->D);
}
bool i1C_INC_E(CPU* cpu) {
    return INC_r8(cpu, &cpu->E);
}
bool i24_INC_H(CPU* cpu) {
    return INC_r8(cpu, &cpu->H);
}
bool i2C_INC_L(CPU* cpu) {
    return INC_r8(cpu, &cpu->L);
}
bool i3C_INC_A(CPU* cpu) {
    return INC_r8(cpu, &cpu->A);
}

// CP A,r8
bool iB8_CP_A_B(CPU * cpu) {
    return CP_A_r8(cpu, cpu->B);
}
bool iB9_CP_A_C(CPU * cpu) {
    return CP_A_r8(cpu, cpu->C);
}
bool iBA_CP_A_D(CPU * cpu) {
    return CP_A_r8(cpu, cpu->D);
}
bool iBB_CP_A_E(CPU * cpu) {
    return CP_A_r8(cpu, cpu->E);
}
bool iBC_CP_A_H(CPU * cpu) {
    return CP_A_r8(cpu, cpu->H);
}
bool iBD_CP_A_L(CPU * cpu) {
    return CP_A_r8(cpu, cpu->L);
}
bool iBF_CP_A_A(CPU * cpu) {
    return CP_A_r8(cpu, cpu->A);
}
// CP A,[HL]
bool iBE_CP_A_HL(CPU* cpu) {
    auto address = cpu->HL();
    auto value = cpu->GetBus()->Read8(address);
    return CP_A_r8(cpu, value);
}
// CP A,n8
bool iFE_CP_A_n8(CPU* cpu) {
    return CP_A_r8(cpu, cpu->Fetch8());
}


bool CP_A_r8(CPU* cpu, std::uint8_t r8) {
    auto result = cpu->A - r8;
    cpu->SetFlags(result == 0, true, (cpu->A & 0xF) < (r8 & 0xF), cpu->A < r8);
    return true;
}
bool SBC_A_r8(CPU* cpu, std::uint8_t r8) {
    auto carry = cpu->FlagCarry();
    int result_full = cpu->A - r8 - carry;
    auto result = static_cast<std::uint8_t>(result_full);
    bool half_carry = ((cpu->A & 0xF) - (r8 & 0xF) - carry) < 0;
    cpu->SetFlags(result == 0, true, half_carry, result_full < 0);
    cpu->A = result;
    return true;
}
