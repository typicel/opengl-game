#pragma once

#include "Shader.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "glad/glad.h"
#include "ResourceManager.h"

class SpriteRenderer {
public:
    SpriteRenderer(const char* vShaderFile, const char* fShaderFile);
    ~SpriteRenderer();

    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    uint32_t quadVAO;
    void initRenderData();
};

