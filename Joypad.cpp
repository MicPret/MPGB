#include "Joypad.h"

#include <GLFW/glfw3.h>

#include <cassert>
#include <cstdio>

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool Joypad::Connect(GLFWwindow* window) {
    if (!window)
        return false;
    InitDefault();
    // TODO Load props
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, input_callback);
    return true;
}

std::uint8_t Joypad::GetValue() const {
    std::uint8_t upper = m_Value & 0xF0;
    if ((upper & 0x20) == 0)
        return upper | m_Buttons;
    if ((upper & 0x10) == 0)
        return upper | m_Directions;
    return upper | 0xF;
}

void Joypad::SetValue(std::uint8_t value) {
    m_Value = value & 0xF0;
}

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_REPEAT)
        return;
    auto joypad = static_cast<Joypad*>(glfwGetWindowUserPointer(window));
    auto bit = joypad->GetBit(key);
    if (bit == -1)
        return;
    auto& reg = joypad->IsDirection(key)
        ? joypad->m_Directions
        : joypad->m_Buttons;

    reg = (action == GLFW_RELEASE)
        ? reg | (1 << bit)
        : reg & ~(1 << bit);
}

void Joypad::InitDefault() {
    m_A = GLFW_KEY_L;
    m_B = GLFW_KEY_K;
    m_Start = GLFW_KEY_SPACE;
    m_Select = GLFW_KEY_ENTER;
    m_Up = GLFW_KEY_W;
    m_Left = GLFW_KEY_A;
    m_Down = GLFW_KEY_S;
    m_Right = GLFW_KEY_D;
}

bool Joypad::IsDirection(int key) const {
    return (m_Up == key) || (m_Left == key) || (m_Down == key) || (m_Right == key);
}

unsigned Joypad::GetBit(int key) const {
    if ((key == m_A) || (key == m_Right))
        return 0;
    if ((key == m_B) || (key == m_Left))
        return 1;
    if ((key == m_Select) || (key == m_Up))
        return 2;
    if ((key == m_Start) || (key == m_Down))
        return 3;
    return -1;
}
