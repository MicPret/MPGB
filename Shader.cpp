#include <mpgb/Shader.h>

#ifndef __EMSCRIPTEN__
static constexpr char vertex_src[] =
    "#version 450 core\n"
    "in vec2 position;\n"
    "out vec2 v_TexCoords;\n"
    "void main() {\n"
    "   v_TexCoords = (0.5 * position) + vec2(0.5);\n"
    "   v_TexCoords.y = 1.0 - v_TexCoords.y;\n"
    "   gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

static constexpr char fragment_src[] =
    "#version 450 core\n"
    "uniform sampler2D u_Texture;\n"
    "in vec2 v_TexCoords;\n"
    "out vec4 f_Color;\n"
    "void main() {\n"
    "   vec3 col = texture(u_Texture, v_TexCoords).rgb;\n"
    "   vec3 compl = vec3(0.87, 1.0, 0.85);\n"
    "   col = compl - (compl * col);\n"
    "   f_Color = vec4(col, 1.0);\n"
    "}\n";
#else
static constexpr char vertex_src[] =
    "#version 300 es\n"
    "in vec2 position;\n"
    "out vec2 v_TexCoords;\n"
    "void main() {\n"
    "   v_TexCoords = (0.5 * position) + vec2(0.5);\n"
    "   v_TexCoords.y = 1.0 - v_TexCoords.y;\n"
    "   gl_Position = vec4(position, 0.0, 1.0);\n"
    "}\n";

static constexpr char fragment_src[] =
    "#version 300 es\n"
    "precision highp float;\n"
    "uniform sampler2D u_Texture;\n"
    "in vec2 v_TexCoords;\n"
    "out vec4 f_Color;\n"
    "void main() {\n"
    "   vec3 col = texture(u_Texture, v_TexCoords).rgb;\n"
    "   vec3 compl = vec3(0.87, 1.0, 0.85);\n"
    "   col = compl - (compl * col);\n"
    "   f_Color = vec4(col, 1.0);\n"
    "}\n";
#endif

std::string GetVertexShaderSource() {
    return std::string(vertex_src);
}
std::string GetFragmentShaderSource() {
    return std::string(fragment_src);
}

