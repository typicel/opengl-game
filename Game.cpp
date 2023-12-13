#include <memory>
#include <iostream>
#include "include/Game.h"
#include "include/ResourceManager.h"

Game::Game(int width, int height, GLFWwindow* window) : m_Window(window) {
    // Load shader for SpriteRenderer
    Shader sprite_shader = ResourceManager::LoadShader("C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.vert", "C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.frag", "sprite_shader");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    sprite_shader.Use();
    sprite_shader.SetInteger("image", 0);
    sprite_shader.SetMatrix4("projection", projection);
    this->m_Renderer = std::make_shared<SpriteRenderer>(sprite_shader);

    // Load all game entities
    Texture2D nugget_texture = ResourceManager::LoadTexture("C:/Users/tyler/Projects/renderer/Assets/Sprites/nugglet.png", "nugglet", true);
    auto nugget = std::make_shared<Entity>(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 300.0f), nugget_texture, glm::vec3(1.f, 0.f, 0.f));

    m_Entities.push_back(nugget);

    InputManager::setupKeyInputs(m_Window);
    Input = new InputManager(std::vector<int> {GLFW_KEY_ESCAPE, GLFW_KEY_D, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_W});
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
    // Render all entities on the screen, do other stuff here too, like handle input and such
    for(auto entity: m_Entities) {
        entity->Draw(m_Renderer.get());
    }
}
