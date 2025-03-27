#include <mpgb/mapper/MBC3.h>
#include <mpgb/Print.h>

#include <algorithm>
#include <cassert>

MBC3::MBC3(const std::uint8_t* data) : Mapper(data) {
    m_RAMBanks.emplace_back();
}

std::uint8_t MBC3::Read8(std::uint16_t address) const {
    // ROM
    if (address < 0x4000) {
        return m_ROMBanks.front()[address];
    }
    if (address < 0x8000) {
        unsigned bank_selection = m_ROMBankNo != 0 ? m_ROMBankNo : 1;
        unsigned offset = address - ROMBankSize;
        return m_ROMBanks[bank_selection][offset];
    }
    // RAM / RTC
    if ((address >= 0xA000) && (address < 0xC000)) {
        if (!m_EnableRAMAndTimer) [[unlikely]] {
            PRINTF("[READ] [MBC3] RAM and RTC disabled: %04X\n", address);
            return -1;
        }
        if (m_RAMBankNoRTCSelect < 0x08) {  // RAM
            unsigned offset = address - 0xA000;
            unsigned bank_select = m_RAMBankNoRTCSelect != 0 ? m_RAMBankNoRTCSelect : 1;
            if (bank_select >= m_RAMBanks.size()) [[unlikely]] {
                PRINTF("[READ] [MBC3] Not enough RAM: %u/%zu\n", bank_select, m_RAMBanks.size());
                return -1;
            }
            return m_RAMBanks[bank_select][offset];
        } else {                            // RTC
            // TODO implement RTC
            return -1;
        }
    }
    // INVALID
    PRINTF("[READ] [MBC3] INVALID: %04X\n", address);
    return -1;
}

bool MBC3::Write8(std::uint16_t address, std::uint8_t value) {
    // Registers
    if (address < 0x2000) {
        switch (value) {
        case 0x0A:
            m_EnableRAMAndTimer = true;
            break;
        case 0x00:
            m_EnableRAMAndTimer = false;
            break;
        default:
            return false;
        }
        return true;
    }
    if (address < 0x4000) {
        m_ROMBankNo = (value & 0x7F);
        return true;
    }
    if (address < 0x6000) {
        m_RAMBankNoRTCSelect = value;
        return true;
    }
    if (address < 0x8000) {
        // TODO implement RTC (Latch clock data)
        return false;
    }
    // INVALID
    if ((address < 0xA000) || (address >= 0xC000)) [[unlikely]] {
        PRINTF("[WRITE] [MBC3] INVALID:\t%04X | %02X\n", address, value);
        return false;
    }
    // RAM / RTC
    if (!m_EnableRAMAndTimer) [[unlikely]] {
        PRINTF("[WRITE] [MBC3] RAM and RTC disabled: %04X\n", address);
        return false;
    }
    // TODO
    return false;
}

MBC3::RTC& MBC3::GetRTC() {
    auto& fake_bank = m_RAMBanks.back();
    auto* raw = fake_bank.data();
    auto* rtc = reinterpret_cast<RTC*>(raw);
    return *rtc;
}

const MBC3::RTC& MBC3::GetRTC() const {
    const auto& fake_bank = m_RAMBanks.back();
    const auto* raw = fake_bank.data();
    const auto* rtc = reinterpret_cast<const RTC*>(raw);
    return *rtc;
}
