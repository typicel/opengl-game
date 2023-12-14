#include "include/Entity.h"

Entity::Entity()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite() {}

Entity::Entity(b2World& world, glm::vec2 pos, glm::vec2 size, Texture2D sprite, bool isStatic, glm::vec3 color, glm::vec2 velocity)
    : Position(pos), Size(size), Sprite(sprite), Color(color), Velocity(velocity), Rotation(0.0f) {

    b2BodyDef bodyDef;

    if(isStatic)
        bodyDef.type = b2_staticBody;
    else
        bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(pos.x, pos.y);
    this->physicsBody = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size.x/2, size.y/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    physicsBody->CreateFixture(&fixtureDef);
}

void Entity::Draw(SpriteRenderer *renderer) {
    renderer->DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void Entity::Move(glm::vec2 value) {
    this->Position += value;
}

