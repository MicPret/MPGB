#ifndef MPGB_MBC1_H
#define MPGB_MBC1_H

#include "Mapper.h"

class MBC1 : public Mapper {
public:
    MBC1(const std::uint8_t* data);
    std::uint8_t Read8(std::uint16_t address) const final;
    bool Write8(std::uint16_t address, std::uint8_t value) final;
private:
    std::uint8_t m_ROMSelectLo = 0;
    std::uint8_t m_ROMSelectHi = 0;
    bool m_RAMEnabled = false;
    bool m_BankingMode = false;
};

#endif
