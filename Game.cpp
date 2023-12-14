#include <memory>
#include <iostream>
#include "include/Game.h"
#include "include/ResourceManager.h"

Game::Game(int width, int height, GLFWwindow* window) : m_Window(window) {
    // Load shader for SpriteRenderer
    this->m_Renderer = std::make_shared<SpriteRenderer>(
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.vert",
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.frag"
    );

    this->world = new b2World(b2Vec2(0.f, 10.f));
    // Load all game entities
    Texture2D nugget_texture = ResourceManager::LoadTexture("C:/Users/tyler/Projects/renderer/Assets/Sprites/nugglet.png", "nugglet", true);
    auto nugget = new Entity(this->world, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 300.0f), nugget_texture, glm::vec3(1.f, 0.f, 0.f));
    this->m_Entities.push_back(nugget);

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

    this->world->Step(timeStep, velocityIterations, positionIterations);

    // Render all entities on the screen, do other stuff here too, like handle input and such
    for(auto entity: m_Entities) {
        auto pos = entity->physicsBody->GetPosition();
        entity->Position = glm::vec2(pos.x, pos.y);

        entity->Draw(m_Renderer.get());
    }
}
