//
// Created by tyler on 12/11/2023.
//

#ifndef RENDERER_TEXTURE2D_H
#define RENDERER_TEXTURE2D_H

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


#endif //RENDERER_TEXTURE2D_H
