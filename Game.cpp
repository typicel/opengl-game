#include <memory>
#include <iostream>
#include "include/Game.h"
#include "include/ResourceManager.h"

Game::Game(int width, int height, GLFWwindow* window) : m_Window(window), world(b2Vec2(0.f, 10.f)), width(width), height(height),
                                                        m_debugDraw(width, height) {
    // Load shader for SpriteRenderer
    this->m_Renderer = std::make_shared<SpriteRenderer>( "sprite.vert", "sprite.frag", width, height);
    // Load all game entities
    Texture2D nugget_texture = ResourceManager::LoadTexture("C:/Users/tyler/Projects/renderer/Assets/Sprites/nugglet.png", "nugglet", true);
    auto nugget = new Entity(world, glm::vec2(100.0f, 0.0f), glm::vec2(50.0f, 50.0f), nugget_texture, false,glm::vec3(0.5f, 0.f, 0.5));
    this->m_Entities.push_back(nugget);

    auto nugget2 = new Entity(world, glm::vec2(125.0f, 100.f), glm::vec2(50.0f, 50.0f), nugget_texture, false,glm::vec3(0.5f, 0.f, 0.5));
    this->m_Entities.push_back(nugget2);

    auto floor = new Entity(world, glm::vec2(0.0f, 500.f), glm::vec2(1200.f, 100.f), nugget_texture, true, glm::vec3(0.5f, 0.5f, 0.5f));
    this->m_Entities.push_back(floor);

    InputManager::setupKeyInputs(m_Window);
    this->Input = new InputManager(std::vector<int> {GLFW_KEY_ESCAPE, GLFW_KEY_D, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_W});
}

void Game::Update() {
    if(Input->getIsKeyDown(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_Window, 1);

    if(Input->getIsKeyDown(GLFW_KEY_D))
        m_Entities[0]->Move(glm::vec2(5.f, 0.f));

    if(Input->getIsKeyDown(GLFW_KEY_A))
        m_Entities[0]->Move(glm::vec2(-5.f, 0.f));

    if(Input->getIsKeyDown(GLFW_KEY_W))
        m_Entities[0]->Move(glm::vec2(0.f, -5.f));

    if(Input->getIsKeyDown(GLFW_KEY_S))
        m_Entities[0]->Move(glm::vec2(0.f, 5.f));
}

void Game::Render() {
    float timeStep = 1.f / 60.f;
    int32_t velocityIterations = 6;
    int32_t positionIterations = 6;

    this->world.Step(timeStep, velocityIterations, positionIterations);

    m_debugDraw.DrawRectangle(0.f, 0.f, 100.f, 100.f);
    m_debugDraw.DrawRectangle(width/2, height/2, 100.f, 100.f);
    m_debugDraw.DrawRectangle(width-100, height-100, 100.f, 100.f);

    // Render all entities on the screen, do other stuff here too, like handle input and such
    for(auto entity: m_Entities) {
        m_Renderer->DrawSprite(*entity);

        b2AABB aabb = entity->physicsBody->GetFixtureList()->GetAABB(0);
        float x = aabb.lowerBound.x;
        float y = aabb.lowerBound.y;
        float width = aabb.upperBound.x - aabb.lowerBound.x;
        float height = aabb.upperBound.y - aabb.lowerBound.y;
        m_debugDraw.DrawRectangle(x, y, width, height);
    }
}
