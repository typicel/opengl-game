#pragma once
#include <iostream>

#if WIN32
    #define ASSERT(x) if (!(x))  __debugbreak();
    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall())
#elif __APPLE__
    #define ASSERT(x) if (!(x))  __builtin_trap();
    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall())
#endif

static void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall() {
    while(GLenum error = glGetError()) {
        std::cout << "Error code" << std::endl;
        return false;
    }
    return true;
}
