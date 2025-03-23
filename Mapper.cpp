#include <mpgb/mapper/Mapper.h>
#include <mpgb/CartridgeHeader.h>
#include <mpgb/Print.h>

Mapper::Mapper(const std::uint8_t* data) {
    auto header = CartridgeHeader(data);
    unsigned rom_banks = (1 << header.romSize) * 2;
    m_ROMBanks.resize(rom_banks);
    for (std::size_t i = 0; i < rom_banks; ++i) {
        auto& bank = m_ROMBanks[i];
        auto offset = i * bank.size();
        std::copy(data + offset, data + offset + bank.size(), bank.data());
    }
    PRINTF("ROM Banks: %u\n", rom_banks);
    unsigned ram_banks;
    switch (header.ramSize) {
    case 0:
        ram_banks = 0;
        break;
    case 2:
        ram_banks = 1;
        break;
    case 3:
        ram_banks = 4;
        break;
    case 4:
        ram_banks = 16;
        break;
    case 5:
        ram_banks = 8;
        break;
    default:
        PRINTF("Invalid RAM size in header: %u\n", (unsigned)header.ramSize);
        ram_banks = 0;
        break;
    }
    m_RAMBanks.resize(ram_banks);
    PRINTF("RAM Banks: %u\n", ram_banks);
    fflush(stdout);
}
