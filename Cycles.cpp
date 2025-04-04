#include <mpgb/Cycles.h>

constexpr std::array<Cycles, 512> cycles = {
        // 0x
        4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4,
        // 1x
        4, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4,
        // 2x
        {12, 8}, 12, 8, 8, 4, 4, 8, 4, {12, 8}, 8, 8, 8, 4, 4, 8, 4,
        // 3x
        {12, 8}, 12, 8, 8, 12, 12, 12, 4, {12, 8}, 8, 8, 8, 4, 4, 8, 4,
        // 4x
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // 5x
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // 6x
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // 7x
        8, 8, 8, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4,
        // 8x
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // 9x
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // Ax
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // Bx
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        // Cx
        {20, 8}, 12, {16, 12}, 16, {24, 12}, 16, 8, 16, {20, 8}, 16, {16, 12}, 4, {24, 12}, 24, 8, 16,
        // Dx
        {20, 8}, 12, {16, 12}, 0, {24, 12}, 16, 8, 16, {20, 8}, 16, {16, 12}, -1, {24, 12}, -1, 8, 16,
        // Ex
        12, 12, 8, -1, -1, 16, 8, 16, 16, 4, 16, -1, -1, -1, 8, 16,
        // Fx
        12, 12, 8, 4, -1, 16, 8, 16, 12, 8, 16, 4, -1, -1, 8, 16,
        // PREFIX
        // 0x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // 1x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // 2x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // 3x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // 4x
        8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
        // 5x
        8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
        // 6x
        8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
        // 7x
        8, 8, 8, 8, 8, 8, 12, 8, 8, 8, 8, 8, 8, 8, 12, 8,
        // 8x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // 9x
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Ax
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Bx
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Cx
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Dx
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Ex
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        // Fx
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
};

const std::array<Cycles, 512>& GetCyclesTable() {
    return cycles;
}
