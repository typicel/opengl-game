#pragma once

#include <cstdint>

class Texture2D {
public:
    uint32_t ID;
    uint32_t Width, Height;
    uint32_t InternalFormat;
    uint32_t ImageFormat;

    uint32_t Wrap_S;
    uint32_t Wrap_T;
    uint32_t Filter_Min;
    uint32_t Filter_Max;

    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;

};

