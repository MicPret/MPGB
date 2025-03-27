#include <mpgb/mapper/MBC2.h>
#include <mpgb/Print.h>

#include <algorithm>
#include <cassert>

MBC2::MBC2(const std::uint8_t* data) : Mapper(data) {
    m_RAMBanks.resize(1);
}

std::uint8_t MBC2::Read8(std::uint16_t address) const {
    // ROM
    if (address < 0x8000) {
        unsigned bank_selection;
        unsigned offset;
        if (address < 0x4000) {
            bank_selection = 0;
            offset = address;
        } else {
            bank_selection = m_ROMSelect != 0 ? m_ROMSelect : 1;
            bank_selection %= m_ROMBanks.size();
            offset = address - ROMBankSize;
        }
        return m_ROMBanks[bank_selection][offset];
    }
    // RAM
    if ((address >= 0xA000) && (address < 0xC000)) {
        if (!m_RAMEnabled) [[unlikely]] {
            PRINTF("[READ] [MBC2] RAM disabled: %04X\n", address);
            return -1;
        }
        unsigned offset = address & 0x1FF;
        return m_RAMBanks.front()[offset]; // TODO check
    }
    // INVALID
    PRINTF("[READ] [MBC2] INVALID: %04X\n", address);
    return -1;
}

bool MBC2::Write8(std::uint16_t address, std::uint8_t value) {
    if (address < 0x4000) {
        bool bit8 = (address & 0x100) != 0;
        if (!bit8) {
            m_RAMEnabled = (value & 0xF) == 0xA;
        } else {
            m_ROMSelect = value & 0xF;
        }
        return true;
    }
    // INVALID
    if ((address < 0xA000) || (address >= 0xC000)) [[unlikely]] {
        PRINTF("[WRITE] [MBC2] INVALID:\t%04X | %02X\n", address, value);
        return false;
    }
    // RAM
    if (!m_RAMEnabled) [[unlikely]] {
        PRINTF("[READ] [MBC2] RAM disabled: %04X\n", address);
        return false;
    }
    unsigned offset = address & 0x1FF;
    m_RAMBanks.front()[offset] = value;
    return true;
}
