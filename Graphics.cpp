#include <mpgb/Graphics.h>
#include <mpgb/Print.h>
#include <mpgb/Shader.h>

#include <array>
#include <cstdint>
#include <cstdlib>

static GLuint s_VAO;
static GLuint s_VBO;
static GLuint s_Texture;
static GLuint s_Program;
static bool s_Init = false;

static constexpr int ScreenWidth = 160;
static constexpr int ScreenHeight = 144;

static void InitProgram();

static void check_shader(GLuint shaderID);
static void check_program(GLuint programID);
static GLuint compile_shader(GLenum type, const char* source);
static GLuint link_program(GLuint vertexShader, GLuint fragmentShader);

GLFWwindow* InitGraphics() {
    // TODO if (s_Init) return ???
    if (glfwInit() == GLFW_FALSE) {
        PUTS("GLFW initialization failed!");
        return nullptr;
    }
    PUTS("GLFW initialized");

#ifdef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
#endif

    auto window = glfwCreateWindow(ScreenWidth * 4, ScreenHeight * 4, "mpgb", nullptr, nullptr);
    if (!window) {
        PUTS("Failed to create window!");
        glfwTerminate();
        return nullptr;
    }
    PUTS("Window created succesfully");
    glfwSetWindowSizeLimits(window, ScreenWidth, ScreenHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* handle, int width, int height) {
        glViewport(0, 0, width, height);
    });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* handle, int width, int height) {
        glfwSetWindowAspectRatio(handle, ScreenWidth, ScreenHeight);
    });

    glfwMakeContextCurrent(window);
    PUTS("Attached context to window");

#ifndef __EMSCRIPTEN__
    if (!gladLoadGL(glfwGetProcAddress)) {
        PUTS("Failed to load OpenGL!");
        glfwTerminate();
        return nullptr;
    }
#endif

    std::array vertices = {
        -1.0f,  -1.0f,
        1.0f,   -1.0f,
        1.0f,   1.0f,
        1.0f,   1.0f,
        -1.0f,  1.0f,
        -1.0f,  -1.0f
    };

#ifndef __EMSCRIPTEN__
    glGenVertexArrays(1, &s_VAO);
    glBindVertexArray(s_VAO);
#endif
    glGenBuffers(1, &s_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const void*)0);
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &s_Texture);
    glBindTexture(GL_TEXTURE_2D, s_Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ScreenWidth, ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    InitProgram();
    auto texloc = glGetUniformLocation(s_Program, "u_Texture");
    glUniform1i(texloc, 0);

    glClearColor(0.5f, 0.7f, 0.7f, 1.0f);

    s_Init = true;
    return window;
}

void UploadTextureData(const std::uint8_t* data) {
    std::array<std::uint8_t, ScreenWidth * ScreenHeight * 3> arr;
    for (auto i = 0; i < (arr.size() / 3); ++i) {
        arr[i * 3] = data[i];
        arr[i * 3 + 1] = data[i];
        arr[i * 3 + 2] = data[i];
    }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ScreenWidth, ScreenHeight, GL_RGB, GL_UNSIGNED_BYTE, arr.data());
}


void TerminateGraphics() {
    if (!s_Init)
        return;
    glDeleteBuffers(1, &s_VBO);
#ifndef __EMSCRIPTEN__
    glDeleteVertexArrays(1, &s_VAO);
#endif
    glDeleteTextures(1, &s_Texture);
    glDeleteProgram(s_Program);
    glfwMakeContextCurrent(nullptr);
    glfwTerminate();
    s_Init = false;
}

void InitProgram() {
    auto vertex_src = GetVertexShaderSource();
    auto fragment_src = GetFragmentShaderSource();
    auto vertex = compile_shader(GL_VERTEX_SHADER, vertex_src.c_str());
    auto fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_src.c_str());
    s_Program = link_program(vertex, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glUseProgram(s_Program);
}



void check_shader(GLuint shader) {
    GLint success;
    std::array<GLchar, 512> info_log;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, info_log.size(), nullptr, info_log.data());
        printf("Shader compilation failed: %s\n", info_log.data());
    }
}
void check_program(GLuint program) {
    GLint success;
    std::array<GLchar, 512> info_log;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, info_log.size(), nullptr, info_log.data());
        printf("Program linking failed: %s\n", info_log.data());
    }
}
GLuint compile_shader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    check_shader(shader);
    return shader;
}
GLuint link_program(GLuint vertex, GLuint fragment) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    check_program(program);
    return program;
}
