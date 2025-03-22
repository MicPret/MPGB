#include "PPU.h"
#include "Bus.h"
#include "Graphics.h"
#include "InterruptFlag.h"
#include "OBJ.h"
#include "Print.h"
#include "utils.h"

#include <algorithm>
#include <cassert>

static constexpr unsigned DotsPerMode2 = 80;
static constexpr unsigned DotsPerMode3 = 172;
static constexpr unsigned DotsPerMode0 = 204;
static constexpr unsigned DotsPerScanline = DotsPerMode2 + DotsPerMode3 + DotsPerMode0;
static constexpr unsigned DotsPerMode1 = DotsPerScanline * 10;
static constexpr unsigned Scanlines = 144;

PPUResult PPU::Tick(unsigned cycles) {
    PPUResult result = PPUWorking;
    if (!IsActive())
        return result;
    m_Cycles += cycles;

    switch (Mode()) {
    case Mode0HBlank:
        if (m_Cycles > DotsPerMode0) {
            DrawScanline(LY);
            IncrementLY();
            if (LY < 144) {
                SetMode(Mode2OAMScan);
            } else {
                SetMode(Mode1VBlank);
                // TODO check STAT ???
                m_Bus->Signal(InterruptVBlank);
            }
            m_Cycles %= DotsPerMode0;
        }
        break;
    case Mode1VBlank:
        if (m_Cycles > DotsPerScanline) {
            IncrementLY();
            if (LY == 155) {
                if (m_Window == nullptr || glfwWindowShouldClose(m_Window)) [[unlikely]] {
                    return PPUStop;
                }
                Draw();
                glfwSwapBuffers(m_Window);
                glfwPollEvents();
                result = PPUDraw;
                LY = 0;
                SetMode(Mode2OAMScan);
                if (STAT & (1 << 5)) {
                    m_Bus->Signal(InterruptLCD);
                }
            }
            if (LY == LYC) {
                STAT |= (1 << 2);
                if (STAT & (1 << 6)) {
                    m_Bus->Signal(InterruptLCD);
                }
            } else {
                STAT &= ~(1 << 2);
            }
            m_Cycles %= DotsPerScanline;
        }
        break;
    case Mode2OAMScan:
        if (m_Cycles > DotsPerMode2) {
            unsigned height = IsOBJBig() ? 16 : 8;
            m_SelectedOBJs.clear();
            unsigned found = 0;
            for (unsigned i = 0; i < m_OAM.size(); i += sizeof(OBJ)) {
                const auto* raw = m_OAM.data() + i;
                auto obj = reinterpret_cast<const OBJ*>(raw);
                auto line = LY + 16;
                bool fits = (line >= obj->posY) && (line < (obj->posY + height));
                if (fits) {
                    m_SelectedOBJs.push_back(obj);
                    if (m_SelectedOBJs.size() >= 10)
                        break;
                }
            }
            SortOBJs();
            SetMode(Mode3PixelDraw);
            m_Cycles %= DotsPerMode2;
        }
        break;
    case Mode3PixelDraw:
        if (m_Cycles > DotsPerMode3) {
            SetMode(Mode0HBlank);
            if (STAT & (1 << 3)) {
                m_Bus->Signal(InterruptLCD);
            }
            m_Cycles %= DotsPerMode3;
        }
        break;
    }
    return result;
}

void PPU::DrawScanline(std::uint8_t line) {
    if (IsBackgroundAndWindowEnabled()) {
        DrawBackground(line);
        if (IsWindowEnabled() && LineInWindow(line)) {
            DrawWindow(line);
        }
    }
    if (IsOBJEnabled()) {
        DrawOBJ(line);
    }
}

void PPU::Draw() {
    UploadTextureData(m_Screen.data());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PPU::EmulateBoot() {
    SCX = 0;
    SCY = 0;
    WX = 0;
    WY = 0;
    LCDC = 0x91;
    STAT = 0x85;
    LY = 0;
    LYC = 0;
    BGP = 0xFC;
}


PPUMode PPU::Mode() const {
    return STAT & 0b11;
}
void PPU::SetMode(PPUMode mode) {
    STAT = (STAT & ~0b11) | mode;
}

unsigned PPU::DotsBeforeNextState() const {
    constexpr std::array dots = { DotsPerMode0, DotsPerMode1, DotsPerMode2, DotsPerMode3 };
    return dots[Mode()] - m_Cycles;
}

std::uint8_t PPU::ReadRegister(std::uint16_t address) const {
    assert(address >= 0xFF40);
    assert(address <= 0xFF4B);
    switch (address) {
    case 0xFF40:
        return LCDC;
    case 0xFF41:
        return STAT;
    case 0xFF42:
        return SCY;
    case 0xFF43:
        return SCX;
    case 0xFF44:
        return LY;
    case 0xFF45:
        return LYC;
    // case 0xFF46: DMA
    case 0xFF47:
        return BGP;
    case 0xFF48:
        return OBP0;
    case 0xFF49:
        return OBP1;
    case 0xFF4A:
        return WY;
    case 0xFF4B:
        return WX;
    default:
        return -1;
    }
}

std::uint8_t PPU::ReadVRAM(std::uint16_t address) const {
    return Mode() != Mode3PixelDraw ? ReadVRAMUnchecked(address): -1;
}

std::uint8_t PPU::ReadVRAMUnchecked(std::uint16_t address) const {
    assert(address >= 0x8000);
    assert(address < 0xA000);
    return m_VRAM[address - 0x8000];
}

std::uint8_t PPU::ReadOAM(std::uint16_t address) const {
    assert(address >= 0xFE00);
    assert(address < 0xFEA0);
    return Mode() < Mode2OAMScan ? m_OAM[address - 0xFE00] : -1;
}

bool PPU::WriteRegister(std::uint16_t address, std::uint8_t value) {
    assert(address >= 0xFF40);
    assert(address <= 0xFF4B);
    constexpr char format[] = "[WRITE] [PPU Register] [%s] %02X\n";
    switch (address) {
    case 0xFF40:
        LCDC = value;
        // PRINTF(format, "LCDC", value);
        break;
    case 0xFF41:
        STAT = (value & ~0b111) | (STAT & 0b111);
        // PRINTF(format, "STAT", value);
        break;
    case 0xFF42:
        SCY = value;
        // PRINTF(format, "SCY", value);
        break;
    case 0xFF43:
        SCX = value;
        // PRINTF(format, "SCX", value);
        break;
    case 0xFF44:
        // PRINTF("Can't write LY!");
        break;
    case 0xFF45:
        LYC = value;
        // PRINTF(format, "LYC", value);
        break;
    case 0xFF47:
        BGP = value;
        // PRINTF(format, "BGP", value);
        break;
    case 0xFF48:
        OBP0 = value;
        // PRINTF(format, "OBP0", value);
        break;
    case 0xFF49:
        OBP1 = value;
        // PRINTF(format, "OBP1", value);
        break;
    case 0xFF4A:
        WY = value;
        // PRINTF(format, "WY", value);
        break;
    case 0xFF4B:
        WX = value;
        // PRINTF(format, "WX", value);
        break;
    default: [[unlikely]]
        PRINTF(format, "Unknown", value);
        return false;
    }
    return true;
}

bool PPU::WriteVRAM(std::uint16_t address, std::uint8_t value) {
    assert(address >= 0x8000);
    assert(address < 0xA000);
    PPUMode mode = Mode();
    if (IsActive() && (mode == Mode3PixelDraw)) [[unlikely]] {
        PRINTF("Failed to write to VRAM!\t%04X | %02X\tMode: %u\n", address, value, mode);
        return false;
    }
    m_VRAM[address - 0x8000] = value;
    return true;    
}

bool PPU::WriteOAM(std::uint16_t address, std::uint8_t value) {
    PPUMode mode = Mode();
    if (mode < Mode2OAMScan) [[likely]] {
        WriteOAMUnchecked(address, value);
        return true;
    }
    PRINTF("Failed to write to OAM!\t%04X | %02X\tMode: %u\n", address, value, mode);
    return false;
}

void PPU::WriteOAMUnchecked(std::uint16_t address, std::uint8_t value) {
    assert(address >= 0xFE00);
    assert(address < 0xFEA0);
    m_OAM[address - 0xFE00] = value;
}

bool PPU::IsActive() const {
    return (LCDC & (1 << 7)) != 0;
}
bool PPU::IsBackgroundAndWindowEnabled() const {
    return (LCDC & (1 << 0)) != 0;
}
bool PPU::IsWindowEnabled() const {
    return (LCDC & (1 << 5)) != 0;
}
bool PPU::IsOBJEnabled() const {
    return (LCDC & (1 << 1)) != 0;
}
bool PPU::IsOBJBig() const {
    return (LCDC & (1 << 2)) != 0;
}
std::uint8_t PPU::GetColor(std::uint8_t color_id, std::uint8_t palette) const {
    assert(color_id < 4);
    return (palette >> (color_id * 2)) & 0b11;
}


void PPU::DrawBackground(std::uint8_t line) {
    std::uint16_t tilemap = (LCDC & (1 << 3)) == 0 ? 0x9800 : 0x9C00;
    for (std::uint8_t i = 0; i < ScreenWidth; ++i) {
        unsigned viewport_x = (i + SCX) & 0xFF;
        unsigned viewport_y = (line + SCY) & 0xFF;
        unsigned map_index_x = viewport_x / 8;
        unsigned map_index_y = viewport_y / 8;
        unsigned map_index = map_index_y * 32 + map_index_x;
        auto id = ReadVRAMUnchecked(tilemap + map_index);

        std::uint16_t tile_addr = (LCDC & (1 << 4)) != 0
            ? 0x8000 | (id << 4)
            : 0x9000 + (static_cast<std::int8_t>(id) * 16);

        std::uint8_t pixel_x = viewport_x % 8;
        std::uint8_t pixel_y = viewport_y % 8;
        auto tileline_addr = tile_addr + pixel_y * 2;
        auto a = ReadVRAMUnchecked(tileline_addr);
        auto b = ReadVRAMUnchecked(tileline_addr + 1);
        auto hi = (a >> (7 - pixel_x)) & 1;
        auto lo = (b >> (7 - pixel_x)) & 1;
        auto color_id = (hi << 1) | lo;
        auto screen_index = line * ScreenWidth + i;
        m_ColorIndices[screen_index] = color_id;
        auto color = GetColor(color_id, BGP);
        auto pixel = color * 85;
        m_Screen[screen_index] = pixel;
    }
}

void PPU::DrawWindow(std::uint8_t line) {
    std::uint16_t tilemap = (LCDC & (1 << 6)) == 0 ? 0x9800 : 0x9C00;
    for (std::uint8_t i = 0; i < ScreenWidth; ++i) {
        if (!PixelInWindow(i))
            continue;
        unsigned window_x = (i + 7) - WX;
        unsigned window_y = line - WY;
        unsigned index_x = window_x / 8;
        unsigned index_y = window_y / 8;
        auto tile_index = index_y * 32 + index_x;
        auto id = ReadVRAMUnchecked(tilemap + tile_index);

        std::uint16_t tile_addr = (LCDC & (1 << 4)) != 0
            ? 0x8000 | (id << 4)
            : 0x9000 + (static_cast<std::int8_t>(id) * 16);

        std::uint8_t pixel_x = window_x % 8;
        std::uint8_t pixel_y = window_y % 8;
        auto tileline_addr = tile_addr + pixel_y * 2;
        auto a = ReadVRAMUnchecked(tileline_addr);
        auto b = ReadVRAMUnchecked(tileline_addr + 1);
        auto hi = (a >> (7 - pixel_x)) & 1;
        auto lo = (b >> (7 - pixel_x)) & 1;
        auto color_id = (hi << 1) | lo;
        auto screen_index = line * ScreenWidth + i;
        m_ColorIndices[screen_index] = color_id;
        auto color = GetColor(color_id, BGP);
        auto pixel = color * 85;
        m_Screen[screen_index] = pixel;
    }
}

void PPU::DrawOBJ(std::uint8_t line) {
    int big = IsOBJBig();
    auto mirror_x = 7;
    auto mirror_y = big ? 15 : 7;
    for (auto obj_ptr : m_SelectedOBJs) {
        auto& obj = *obj_ptr;
        for (unsigned i = 0; i < ScreenWidth; ++i) {
            if (!PixelInOBJ(i, obj))
                continue;
            auto screen_index = line * ScreenWidth + i;
            auto priority = obj.attributes & 0x80;
            if (priority && (m_ColorIndices[screen_index] != 0))
                continue;
            auto tile_index = obj.tileIndex & ~big;
            std::uint16_t tile_addr = 0x8000 | (tile_index << 4);
            auto offs_y = (line + 16) - obj.posY;
            bool flip_y = (obj.attributes & (1 << 6)) != 0;
            if (flip_y)
                offs_y = mirror_y - offs_y;
            auto offs_x = (i + 8) - obj.posX;
            bool flip_x = (obj.attributes & (1 << 5)) != 0;
            if (flip_x)
                offs_x = mirror_x - offs_x;
            auto tileline_addr = tile_addr + offs_y * 2;
            auto a = ReadVRAMUnchecked(tileline_addr);
            auto b = ReadVRAMUnchecked(tileline_addr + 1);
            auto hi = (a >> (7 - offs_x)) & 1;
            auto lo = (b >> (7 - offs_x)) & 1;
            auto color_id = (hi << 1) | lo;
            if (color_id == 0)
                continue;
            auto palette = obj.attributes & (1 << 4) ? OBP1 : OBP0;
            auto color = GetColor(color_id, palette);
            auto pixel = color * 85;
            m_Screen[screen_index] = pixel;
        }
    }
}
bool PPU::PixelInOBJ(std::uint8_t screen_x, const OBJ& obj) const {
    auto x = screen_x + 8;
    return (x >= obj.posX) && (screen_x < obj.posX);
}


bool PPU::LineInWindow(std::uint8_t line) const {
    return line >= WY;
}

bool PPU::PixelInWindow(std::uint8_t screen_x) const {
    return (screen_x + 7) >= WX;
}

void PPU::SortOBJs() {
    using u8 = std::uint8_t;
    std::sort(m_SelectedOBJs.begin(), m_SelectedOBJs.end(), [this](const OBJ* a, const OBJ* b) {
        return a->posX > b->posX;
    });
}

PPU::PPU() {
    m_SelectedOBJs.reserve(10);
}

void PPU::IncrementLY() {
    LY++;
    if (LY == LYC) {
        STAT |= (1 << 2);
        if (STAT & (1 << 6)) {
            m_Bus->Signal(InterruptLCD);
        }
    } else {
        STAT &= ~(1 << 2);
    }
}
