#ifndef MPGB_CARTRIDGE_H
#define MPGB_CARTRIDGE_H

#include <mpgb/mapper/Mapper.h>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <vector>

class Cartridge {
public:
    Cartridge() = default;
    bool LoadROM(const std::filesystem::path& file);
    bool LoadROM(const std::uint8_t* data, std::size_t size);
    bool LoadSave(const std::filesystem::path& file);
    bool LoadSave(const std::uint8_t* data, std::size_t size);
    std::uint8_t Read8(std::uint16_t address) const;
    bool Write8(std::uint16_t address, std::uint8_t value);
    std::vector<std::uint8_t> Save() const;
private:
    std::unique_ptr<Mapper> m_Mapper;
};

#endif
