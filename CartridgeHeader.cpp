#include "CartridgeHeader.h"

#include <cassert>

std::string CartridgeHeader::GetTitle() const {
    return std::string((const char*)title.data(), title.size());
}

CartridgeHeader::CartridgeHeader(const std::uint8_t* rom) {
    assert(rom);
    auto* header_ptr = reinterpret_cast<std::uint8_t*>(this);
    auto header_start = rom + 0x100;
    auto header_end = rom + 0x150;
    std::copy(header_start, header_end, header_ptr);
}
