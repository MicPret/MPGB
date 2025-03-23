#ifndef MPGB_UTILS_H
#define MPGB_UTILS_H

#include <cstdint>
#include <type_traits>

std::uint16_t to_r16(std::uint8_t hi, std::uint8_t lo);
void to_r8(std::uint16_t value, std::uint8_t* hi, std::uint8_t* lo);

template <typename T>
constexpr bool get_bit(T num, T bit) {
    static_assert(std::is_integral_v<T>);
    return (num >> bit) & 1;
}

template <typename T>
constexpr T set_bit(T num, unsigned bit, bool value) {
    static_assert(std::is_integral_v<T>);
    auto shifted = static_cast<int>(value) << bit;
    auto mask = ~(1 << bit);
    return (num & mask) | shifted;
}


#endif
