#pragma once

#include <glm/glm.hpp>
#include "Texture2D.h"
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>

class Entity {
public:
    Entity();
    Entity(b2World& world, glm::vec2 pos, glm::vec2 size, Texture2D sprite, bool isStatic,glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    glm::vec2 GetPosition();

    void SetPosition(glm::vec2 value);
    void SetColor(glm::vec3 color);

    Texture2D Sprite;
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    float Rotation;

    bool isStatic;

    b2Body* physicsBody;
};
