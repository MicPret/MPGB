cmake_minimum_required(VERSION 3.31)

target_include_directories(mpgb PRIVATE include)

target_compile_definitions(mpgb PUBLIC GLFW_INCLUDE_NONE=1)

if(EMSCRIPTEN)
  target_link_options(mpgb PUBLIC "--use-port=contrib.glfw3")
else()
  target_sources(mpgb PRIVATE gl.c)
  
  include(FetchContent)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3
    FIND_PACKAGE_ARGS
  )
  FetchContent_MakeAvailable(glfw)
endif()

target_link_libraries(mpgb glfw)
