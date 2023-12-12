//
// Created by tyler on 12/11/2023.
//
#pragma once

#include <iostream>
#define ASSERT(x) if (!(x))  __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall())

static void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool GLLogCall()
{
    while(GLenum error = glGetError())
    {
        std::cout << "Error code" << std::endl;
        return false;
    }
    return true;
}
