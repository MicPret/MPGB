#ifndef MPGB_MBC2_H
#define MPGB_MBC2_H

#include "Mapper.h"

class MBC2 : public Mapper {
public:
    MBC2(const std::uint8_t* data);
    std::uint8_t Read8(std::uint16_t address) const final;
    bool Write8(std::uint16_t address, std::uint8_t value) final;
private:
    std::uint8_t m_ROMSelect = 0;
    bool m_RAMEnabled = false;
};

#endif
