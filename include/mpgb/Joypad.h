#ifndef MPGB_JOYPAD_H
#define MPGB_JOYPAD_H

#include <cstdint>

class GLFWwindow;

class Joypad {
public:
    std::uint8_t GetValue() const;
    void SetValue(std::uint8_t value);
    bool Connect(GLFWwindow* window);
private:
    std::uint8_t m_Value = 0xFF;
    std::uint8_t m_Buttons = 0xFF;
    std::uint8_t m_Directions = 0xFF;
    int m_A;
    int m_B;
    int m_Start;
    int m_Select;
    int m_Up;
    int m_Left;
    int m_Down;
    int m_Right;
    
    void InitDefault();
    bool IsDirection(int key) const;
    unsigned GetBit(int key) const;
    friend void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
