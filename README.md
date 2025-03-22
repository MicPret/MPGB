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
2. Build the project using CMake
3. Run it
    ```
    ./mpgb [your_game.gb]
    ```

## Supported mappers
- [x] NoMBC
- [x] MBC1
- [x] MBC2
- [ ] MBC3
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
- Remappable joypad
- Fix browser weird behaviour
- Android support
