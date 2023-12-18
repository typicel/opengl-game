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

    bodyDef.position.Set(pos.x + (size.x/2), pos.y + (size.y/2));
    this->physicsBody = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size.x/2, size.y/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    physicsBody->CreateFixture(&fixtureDef);
}

glm::vec2 Entity::GetPosition() {
    return glm::vec2(this->physicsBody->GetPosition().x - (this->Size.x/2), this->physicsBody->GetPosition().y - (this->Size.y/2));
}

void Entity::SetPosition(glm::vec2 value) {
    this->physicsBody->SetTransform(b2Vec2(value.x + (this->Size.x/2), value.y + (this->Size.y/2)), this->physicsBody->GetAngle());
}

void Entity::SetColor(glm::vec3 color) {
    this->Color = color;
}

