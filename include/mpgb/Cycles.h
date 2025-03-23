#ifndef MPGB_CYCLES_H
#define MPGB_CYCLES_H

#include <array>

struct Cycles {
    unsigned taken;
    unsigned untaken;

    constexpr Cycles() : taken(-1), untaken(-1) {}
    constexpr Cycles(unsigned cycles) : taken(cycles), untaken(cycles) {}
    constexpr Cycles(unsigned taken, unsigned untaken) : taken(taken), untaken(untaken) {}
};

const std::array<Cycles, 512>& GetCyclesTable();

#endif
