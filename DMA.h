#ifndef MPGB_DMA_H
#define MPGB_DMA_H

#include <cstdint>

class Bus;
class PPU;

class DMA {
public:
    void SetBus(Bus* bus);
    void InitiateTransfer(std::uint16_t address);
    void Tick(unsigned cycles);
private:
    Bus* m_Bus = nullptr;
    int m_Cycles = 0;
    std::uint16_t m_AddressStart = 0;
};

#endif
