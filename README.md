# MPGB
MPGB is a Game Boy emulator.

## Requirements
### Build
- **CMake** 3.31 or later
### Run
- **OpenGL** 4.5
### Browser Support (optional)
- **Emscripten SDK**

## Instructions
1. Clone the repository
    ```
    git clone https://github.com/MicPret/MPGB.git
    ```
2. Build the project using CMake
    ```
    cd MPGB
    cmake -S . -B build
    cmake --build build
    ```
3. Run it
    ```
    cd build
    ./mpgb [your_game.gb]
    ```

## Supported mappers
- [x] NoMBC
- [x] MBC1
- [x] MBC2
- [ ] MBC3 (WIP)
- [ ] MBC5
- [ ] MBC6
- [ ] MBC7
- [ ] MMM01
- [ ] M161
- [ ] HuC1
- [ ] HuC-3

## TODO
- Better README.md
- Fix OAM and VRAM access issue
- Audio support
- Remappable joypad
- Fix browser weird behaviour
- Android support
