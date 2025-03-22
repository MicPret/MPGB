#include "NoMBC.h"

#include <algorithm>
#include <cassert>
#include <cstdio>

NoMBC::NoMBC(const std::uint8_t* data) : Mapper(data) {
    assert(m_ROMBanks.size() == 2);
    assert(m_RAMBanks.size() <= 1);
}

std::uint8_t NoMBC::Read8(std::uint16_t address) const {
    unsigned bank_id, offset;
    if (address < 0x8000) {
        unsigned bank_id = address > ROMBankSize;
        unsigned offset = address % ROMBankSize;
        return m_ROMBanks[bank_id][offset];
    } else if ((address >= 0xA000) && (address < 0xC000)) {
        assert(!m_RAMBanks.empty());
        return m_RAMBanks[0][address - 0xA000];
    }
    printf("[READ] [Cartridge] %04X\n", address);
    fflush(stdout);
    return -1;
}

bool NoMBC::Write8(std::uint16_t address, std::uint8_t value) {
    if ((address >= 0xA000) && (address < 0xC000)) [[likely]] {
        assert(!m_RAMBanks.empty());
        m_RAMBanks[0][address - 0xA000] = value;
        return true;
    }
    printf("[WRITE] [Cartridge%s] %04X\n", address < 0x8000 ? " ROM" : "", address);
    fflush(stdout);
    return false;
}
