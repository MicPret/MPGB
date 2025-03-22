#include "DMA.h"
#include "Bus.h"
#include "PPU.h"

#include <cassert>

constexpr int TotalCycles = 640;

void DMA::Tick(unsigned cycles) {
    if (m_Cycles <= 0)
        return;
    m_Cycles -= static_cast<int>(cycles);
    if (m_Cycles > 0)
        return;
    assert(m_Bus);
    for (auto i = 0; i < 0xA0; i++) {
        std::uint16_t r_address = m_AddressStart | i;
        std::uint16_t w_address = 0xFE00 | i;
        auto value = m_Bus->Read8(r_address);
        m_Bus->Write8(w_address, value);
    }
}

void DMA::InitiateTransfer(std::uint16_t address) {
    m_AddressStart = address;
    m_Cycles = TotalCycles;
}

void DMA::SetBus(Bus* bus) {
    assert(bus);
    m_Bus = bus;
}
