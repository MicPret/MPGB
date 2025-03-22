#ifndef MPGB_INTERRUPT_FLAG_H
#define MPGB_INTERRUPT_FLAG_H

using InterruptFlag = unsigned;

constexpr InterruptFlag InterruptVBlank =   1 << 0;
constexpr InterruptFlag InterruptLCD =      1 << 1;
constexpr InterruptFlag InterruptTimer =    1 << 2;
constexpr InterruptFlag InterruptSerial =   1 << 3;
constexpr InterruptFlag InterruptJoypad =   1 << 4;

#endif
