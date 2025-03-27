#ifndef MPGB_MBC3_H
#define MPGB_MBC3_H

#include "Mapper.h"

class MBC3 : public Mapper {
public:
    MBC3(const std::uint8_t* data);
    std::uint8_t Read8(std::uint16_t address) const final;
    bool Write8(std::uint16_t address, std::uint8_t value) final;
private:
    std::uint8_t m_EnableRAMAndTimer = false;
    std::uint8_t m_ROMBankNo;
    std::uint8_t m_RAMBankNoRTCSelect;
    
    struct RTC {
        std::uint8_t S;
        std::uint8_t M;
        std::uint8_t H;
        std::uint8_t DL;
        std::uint8_t DH;
    };
    RTC& GetRTC();
    const RTC& GetRTC() const;
};

#endif
