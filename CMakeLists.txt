cmake_minimum_required(VERSION 3.31)

project(mpgb LANGUAGES CXX C)

add_executable(mpgb)

target_compile_features(mpgb PRIVATE cxx_std_20)

add_subdirectory(ext)

target_include_directories(mpgb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(mpgb
    PRIVATE
        main.cpp
        arithmetic8.cpp
        arithmetic16.cpp
        carry.cpp
        bitflag.cpp
        bitshift.cpp
        bitwise.cpp
        interrupt.cpp
        jump.cpp
        load.cpp
        misc.cpp
        stack.cpp
        utils.cpp
        Bus.cpp
        Cartridge.cpp
        CartridgeHeader.cpp
        CPU.cpp
        Cycles.cpp
        DMA.cpp
        Graphics.cpp
        InstructionFunc.cpp
        Joypad.cpp
        Mapper.cpp
        MBC1.cpp
        MBC2.cpp
        NoMBC.cpp
        PPU.cpp
        Shader.cpp
)

if(EMSCRIPTEN)
    target_compile_definitions(mpgb PUBLIC MPGB_ENABLE_PRINT=1)
    target_link_options(mpgb
        PUBLIC
            "-O3"
            "-sMIN_WEBGL_VERSION=2"
            "-sMAX_WEBGL_VERSION=2"
            "-sSTACK_SIZE=128MB"
            "-sEXPORTED_FUNCTIONS=[_malloc,_free,_Start,_LoadROM]"
            # "--emrun"
    )
    add_custom_command(TARGET mpgb PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/web/
            $<TARGET_FILE_DIR:mpgb>
    )
else()
    target_compile_definitions(mpgb PUBLIC MPGB_ENABLE_PRINT=1)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/roms)
    add_custom_command(TARGET mpgb PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/roms/
            $<TARGET_FILE_DIR:mpgb>/roms/
    )
endif()
