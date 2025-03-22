#ifndef MPGB_CARTRIDGE_HEADER_H
#define MPGB_CARTRIDGE_HEADER_H

#include <array>
#include <cstdint>
#include <string>

struct CartridgeHeader {
    std::array<std::uint8_t, 4> entry;
    std::array<std::uint8_t, 48> logo;
    std::array<std::uint8_t, 16> title;
    std::array<std::uint8_t, 2> newLicenseeCode;
    std::uint8_t sgbFlag;
    std::uint8_t mapperType;
    std::uint8_t romSize;
    std::uint8_t ramSize;
    std::uint8_t destinationCode;
    std::uint8_t oldLicenseeCode;
    std::uint8_t version;
    std::uint8_t checksum;
    std::array<std::uint8_t, 2> globalChecksum;
    
    CartridgeHeader(const std::uint8_t* rom);
    std::string GetTitle() const;
};

#endif
