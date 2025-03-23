#ifndef MPGB_NOMBC_H
#define MPGB_NOMBC_H

#include <array>

#include <mpgb/Cartridge.h>

class NoMBC : public Mapper {
public:
    NoMBC(const std::uint8_t* data);
    std::uint8_t Read8(std::uint16_t address) const final;
    bool Write8(std::uint16_t address, std::uint8_t value) final;
};

#endif
