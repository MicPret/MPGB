#ifndef MPGB_OBJ_H
#define MPGB_OBJ_H

#include <cstdint>

struct OBJ {
    std::uint8_t posY;
    std::uint8_t posX;
    std::uint8_t tileIndex;
    std::uint8_t attributes;
};

#endif
