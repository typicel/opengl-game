#pragma once

#include "Shader.h"
#include "VertexBuffer.h"
#include "glad/glad.h"
#include "ResourceManager.h"
#include "Entity.h"

class SpriteRenderer {
public:
    SpriteRenderer(const char* vShaderFile, const char* fShaderFile, int width, int height);
    ~SpriteRenderer();

    void DrawSprite(const Entity& entity);

private:
    Shader shader;
    uint32_t quadVAO;
    void initRenderData();
};

