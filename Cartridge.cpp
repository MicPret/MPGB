#include "Cartridge.h"
#include "CartridgeHeader.h"
#include "MBC1.h"
#include "MBC2.h"
#include "NoMBC.h"
#include "Print.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

static std::unique_ptr<Mapper> CreateMapper(const std::uint8_t* data, std::size_t size);

bool Cartridge::Load(const std::filesystem::path& file) {
    std::ifstream rom(file, std::ios::binary);
    if (!rom) {
        PRINTF("Failed to load ROM file: %s\n", file.c_str());
        return false;
    }
    auto data = std::vector<std::uint8_t>(std::istreambuf_iterator<char>(rom), {});
    return Load(data.data(), data.size());
}

bool Cartridge::Load(const std::uint8_t* data, std::size_t size) {
    m_Mapper = CreateMapper(data, size);
    return m_Mapper != nullptr;
}

std::uint8_t Cartridge::Read8(std::uint16_t address) const {
    assert(m_Mapper);
    return m_Mapper->Read8(address);
}

bool Cartridge::Write8(std::uint16_t address, std::uint8_t value) {
    assert(m_Mapper);
    return m_Mapper->Write8(address, value);
}

std::unique_ptr<Mapper> CreateMapper(const std::uint8_t* data, std::size_t size) {
    CartridgeHeader header(data);

    std::string title(header.GetTitle());
    PRINTF("Loading %s...\n", title.c_str());
    PRINTF("Mapper type: %02X\n", header.mapperType);
    std::unique_ptr<Mapper> result = nullptr;
    switch (header.mapperType){
    case 0x00:
        result = std::make_unique<NoMBC>(data);
        break;
    case 0x01:
    case 0x02:
    case 0x03:
        result = std::make_unique<MBC1>(data);
        break;
    case 0x05:
    case 0x06:
        result = std::make_unique<MBC2>(data);
        break;
    default:
        PRINTF("Unsupported mapper: %02X\n", header.mapperType);
        break;
    }
    return result;
}

