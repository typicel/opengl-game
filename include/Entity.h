#pragma once

#include "SpriteRenderer.h"

class Entity {
public:
    Entity();
    Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    virtual void Draw(SpriteRenderer* renderer);

    Texture2D Sprite;
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float Rotation;
};
