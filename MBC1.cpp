#include "MBC1.h"
#include "Print.h"

#include <algorithm>
#include <cassert>

// TODO Special MBC1 (multi-carts)

MBC1::MBC1(const std::uint8_t* data) : Mapper(data) {}

std::uint8_t MBC1::Read8(std::uint16_t address) const {
    // ROM
    if (address < 0x8000) {
        unsigned bank_selection;
        unsigned offset;
        if ((address < 0x4000) && !m_BankingMode) {
            bank_selection = 0;
            offset = address;
        } else {
            bank_selection = m_ROMSelectLo != 0 ? m_ROMSelectLo : 1;
            if (m_ROMBanks.size() > 0x1F) {
                bank_selection |= (m_ROMSelectHi << 5);
            }
            bank_selection %= m_ROMBanks.size();
            offset = address - ROMBankSize;
        }
        return m_ROMBanks[bank_selection][offset];
    }
    // RAM
    if ((address >= 0xA000) && (address < 0xC000)) {
        if (!m_RAMEnabled) [[unlikely]] {
            PRINTF("[READ] [MBC1] RAM disabled: %04X\n", address);
            return -1;
        }
        // TODO implement save
        unsigned offset = address - 0xA000;
        unsigned bank_select = (m_BankingMode && (m_ROMSelectHi < m_RAMBanks.size()))
            ? m_ROMSelectHi
            : 0;
        if (bank_select >= m_ROMBanks.size()) [[unlikely]] {
            PRINTF("[READ] [MBC1] Not enough RAM: %u/%zu\n", bank_select, m_RAMBanks.size());
            return -1;
        }
        return m_RAMBanks[bank_select][offset];
    }
    // INVALID
    PRINTF("[READ] [MBC1] INVALID: %04X\n", address);
    return -1;
}

bool MBC1::Write8(std::uint16_t address, std::uint8_t value) {
    // Registers
    if (address < 0x2000) {
        m_RAMEnabled = ((value & 0x0F) == 0xA);
        return true;
    }
    if (address < 0x4000) {
        m_ROMSelectLo = (value & 0x1F);
        return true;
    }
    if (address < 0x6000) {
        m_ROMSelectHi = (value & 0b11);
        return true;
    }
    if (address < 0x8000) {
        m_BankingMode = (value & 1);
        return true;
    }
    // INVALID
    if ((address < 0xA000) || (address >= 0xC000)) [[unlikely]] {
        PRINTF("[WRITE] [MBC1] INVALID:\t%04X | %02X\n", address, value);
        return false;
    }
    // RAM
    if (!m_RAMEnabled) [[unlikely]] {
        PRINTF("[WRITE] [MBC1] RAM disabled: %04X\n", address);
        return -1;
    }
    unsigned offset = address - 0xA000;
    unsigned bank_select = (m_BankingMode && (m_ROMSelectHi < m_RAMBanks.size()))
        ? m_ROMSelectHi
        : 0;
    if (bank_select >= m_RAMBanks.size()) [[unlikely]] {
        PRINTF("[WRITE] [MBC1] Not enough RAM: %u/%lu\t%04X | %02X\n",
            bank_select,
            m_RAMBanks.size(),
            address,
            value);
        return false;
    }
    m_RAMBanks[bank_select][offset] = value;
    return true;
}
