#ifndef MPGB_MAPPER_H
#define MPGB_MAPPER_H

#include <array>
#include <cstdint>
#include <vector>

class Mapper {
public:
    Mapper(const std::uint8_t* data);
    virtual ~Mapper() = default;
    virtual std::uint8_t Read8(std::uint16_t address) const = 0;
    virtual bool Write8(std::uint16_t address, std::uint8_t value) = 0;
protected:
    static constexpr unsigned ROMBankSize = 0x4000;
    static constexpr unsigned RAMBankSize = 0x2000;
    using ROMBank = std::array<std::uint8_t, ROMBankSize>;
    using RAMBank = std::array<std::uint8_t, RAMBankSize>;
    std::vector<ROMBank> m_ROMBanks;
    std::vector<RAMBank> m_RAMBanks;
};

#endif
