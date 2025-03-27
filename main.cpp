#include <mpgb/Bus.h>
#include <mpgb/Cartridge.h>
#include <mpgb/CPU.h>
#include <mpgb/Graphics.h>
#include <mpgb/PPU.h>
#include <mpgb/Print.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

static Bus s_Bus;
static CPU s_CPU;
static PPU s_PPU;
static Cartridge s_Cartridge;
static std::string s_Filename;

extern "C" {
#ifdef __EMSCRIPTEN__
    void main_loop();
    void LoadROM(const std::uint8_t* data, std::size_t size);
#endif
    bool Start();
}

#ifndef __EMSCRIPTEN__
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        PUTS("You must specify a ROM file as argument!");
        return 1;
    }
    if (argc > 1) {
        s_Filename = argv[1];
        auto save_name = s_Filename + ".sav";
        bool success = s_Cartridge.LoadROM(s_Filename);
        if (!success || !std::filesystem::exists(save_name)) {
            return 2;
        }
        PRINTF("Loading save file: %s\n", save_name.c_str());
        s_Cartridge.LoadSave(save_name);
    }
    bool success = Start();

    return success ? 0 : 3;
}
#endif

#ifdef __EMSCRIPTEN__
void main_loop() {
    bool should_stop = !s_Bus.EmulateFrame();
    if (should_stop) {
        emscripten_cancel_main_loop();
        TerminateGraphics();
    }
}

void LoadROM(const std::uint8_t* data, std::size_t size) {
    s_Cartridge.Load(data, size);
}

#endif

bool Start() {
    TerminateGraphics();
    auto window = InitGraphics();
    if (!window) {
        PUTS("Failed to create window!");
        return false;
    }
    PUTS("Graphics loaded!");

    s_Bus.Connect(&s_CPU, &s_PPU, window, &s_Cartridge);
    s_Bus.EmulateBoot(); // TODO load Boot ROM if present

    setvbuf(stdout, nullptr, _IOFBF, 1024);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    bool keep_going;
    do {
        keep_going = s_Bus.EmulateFrame();
        fflush(stdout);
    } while(keep_going);
    
    TerminateGraphics();
#endif
    fflush(stdout);
    setvbuf(stdout, nullptr, _IOLBF, BUFSIZ);
    
    return true;
}
