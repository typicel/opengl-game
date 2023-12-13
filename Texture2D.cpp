#include "include/Texture2D.h"
#include <glad/glad.h>
#include "include/Errors.h"

Texture2D::Texture2D()
    : Width(0), Height(0), InternalFormat(GL_RGB), ImageFormat(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Max(GL_LINEAR), Filter_Min(GL_LINEAR)
{
    GLCall(glGenTextures(1, &this->ID));
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->Width = width;
    this->Height = height;

    GLCall(glBindTexture(GL_TEXTURE_2D, this->ID));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, this->InternalFormat, width, height, 0, this->ImageFormat, GL_UNSIGNED_BYTE, data));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::Bind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, this->ID));
}
