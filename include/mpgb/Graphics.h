#ifndef MPGB_GRAPHICS_API_H
#define MPGB_GRAPHICS_API_H

#ifndef __EMSCRIPTEN__
#include <glad/gl.h>
#else
// #include <glad/gles2.h>
#include <GLES3/gl3.h>
#endif
#include <GLFW/glfw3.h>

#include <cstdint>

GLFWwindow* InitGraphics();
void TerminateGraphics();

void UploadTextureData(const std::uint8_t* data);

#endif
