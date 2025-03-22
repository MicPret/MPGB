#ifndef MPGB_PPU_H
#define MPGB_PPU_H

#include <array>
#include <cstdint>
#include <vector>

using PPUMode = unsigned;
constexpr PPUMode Mode2OAMScan = 2;
constexpr PPUMode Mode3PixelDraw = 3;
constexpr PPUMode Mode0HBlank = 0;
constexpr PPUMode Mode1VBlank = 1;
using PPUResult = unsigned;
constexpr PPUResult PPUWorking = 0;
constexpr PPUResult PPUDraw = 1;
constexpr PPUResult PPUStop = 2;

constexpr unsigned ScreenWidth = 160;
constexpr unsigned ScreenHeight = 144;

class Bus;
struct GLFWwindow;
struct OBJ;

class PPU {
public:
    std::uint8_t LCDC;  // 0xFF40 (LCD Control Register)
    std::uint8_t STAT;  // 0xFF41 (LCD Status Register)
    std::uint8_t SCY;   // 0xFF42 (Scroll Y)
    std::uint8_t SCX;   // 0xFF43 (Scroll X)
    std::uint8_t LY;    // 0xFF44 (LCD Y-Coordinate)
    std::uint8_t LYC;   // 0xFF45 (LY Compare)
    std::uint8_t BGP;   // 0xFF47 (BG Palette data)
    std::uint8_t OBP0;  // 0xFF48 (OBJ Palette 0 data)
    std::uint8_t OBP1;  // 0xFF49 (OBJ Palette 1 data)
    std::uint8_t WY;    // 0xFF4A (Window Y position)
    std::uint8_t WX;    // 0xFF4B (Window X position plus 7)

    PPU();

    PPUResult Tick(unsigned cycles);
    void Draw();
    void EmulateBoot();

    PPUMode Mode() const;
    bool IsActive() const;
    bool IsBackgroundAndWindowEnabled() const;
    bool IsWindowEnabled() const;
    bool IsOBJEnabled() const;
    bool IsOBJBig() const;
    constexpr const auto& Screen() const { return m_Screen; }
    unsigned DotsBeforeNextState() const;

    constexpr void SetBus(Bus* bus) { m_Bus = bus; }
    constexpr void SetWindow(GLFWwindow* window) { m_Window = window; }

    std::uint8_t ReadRegister(std::uint16_t address) const;
    std::uint8_t ReadVRAM(std::uint16_t address) const;
    std::uint8_t ReadOAM(std::uint16_t address) const;
    bool WriteRegister(std::uint16_t address, std::uint8_t value);
    bool WriteVRAM(std::uint16_t address, std::uint8_t value);
    bool WriteOAM(std::uint16_t address, std::uint8_t value);
    void WriteOAMUnchecked(std::uint16_t address, std::uint8_t value);
private:
    unsigned m_Cycles = 0;
    std::array<std::uint8_t, 0x2000> m_VRAM;    // 0x8000 ~ 0x9FFF (Video RAM)
    std::array<std::uint8_t, 0xA0> m_OAM;       // 0xFE00 ~ 0xFE9F (Object attribute memory)
    std::array<std::uint8_t, ScreenWidth * ScreenHeight> m_Screen;
    std::array<std::uint8_t, ScreenWidth * ScreenHeight> m_ColorIndices;
    std::vector<const OBJ*> m_SelectedOBJs;
    Bus* m_Bus = nullptr;
    GLFWwindow* m_Window = nullptr;

    std::uint8_t ReadVRAMUnchecked(std::uint16_t address) const;
    void SetMode(PPUMode mode);
    void DrawScanline(std::uint8_t line);
    void DrawBackground(std::uint8_t line);
    void DrawWindow(std::uint8_t line);
    void DrawOBJ(std::uint8_t line);
    bool LineInWindow(std::uint8_t line) const;
    bool PixelInWindow(std::uint8_t screen_x) const;
    bool PixelInOBJ(std::uint8_t screen_x, const OBJ& obj) const;
    void IncrementLY();
    std::uint16_t GetTileAddress(std::uint8_t tile_id) const;
    std::uint8_t GetColor(std::uint8_t color_id, std::uint8_t palette) const;
    void SortOBJs();
};

#endif
