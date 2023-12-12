//
// Created by tyler on 12/11/2023.
//

#ifndef RENDERER_SPRITERENDERER_H
#define RENDERER_SPRITERENDERER_H

#include "Shader.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    Shader shader;
    uint32_t quadVAO;
    void initRenderData();
};


#endif //RENDERER_SPRITERENDERER_H
