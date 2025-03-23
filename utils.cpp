#include <mpgb/instr/utils.h>

std::uint16_t to_r16(std::uint8_t hi, std::uint8_t lo) {
    return (hi << 8) | lo;
}

void to_r8(std::uint16_t value, std::uint8_t* hi, std::uint8_t* lo) {
    *hi = static_cast<std::uint8_t>(value >> 8);
    *lo = static_cast<std::uint8_t>(value);
}
