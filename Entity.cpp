#include "include/Entity.h"

Entity::Entity()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite() {}

Entity::Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Sprite(sprite), Color(color), Velocity(velocity), Rotation(0.0f) { }

void Entity::Draw(SpriteRenderer *renderer) {
    renderer->DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}


