#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <string>

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

    auto nugget3 = new Entity(world, glm::vec2(0.f, 0.f), glm::vec2(50.0f, 50.0f), nugget_texture, false,glm::vec3(0.5f, 0.f, 0.5));
    this->m_Entities.push_back(nugget3);

    auto floor = new Entity(world, glm::vec2(0.0f, 500.f), glm::vec2(1200.f, 100.f), nugget_texture, true, glm::vec3(0.5f, 0.5f, 0.5f));
    this->m_Entities.push_back(floor);

    InputManager::setupKeyInputs(m_Window);
    this->Input = new InputManager(std::vector<int> {GLFW_KEY_ESCAPE, GLFW_KEY_D, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_W});
}

void Game::Update() {
    if(Input->getIsKeyDown(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_Window, 1);

    if(Input->getIsKeyDown(GLFW_KEY_D))
        m_Entities[0]->SetPosition(glm::vec2(5.f, 0.f));

    if(Input->getIsKeyDown(GLFW_KEY_A))
        m_Entities[0]->SetPosition(glm::vec2(-5.f, 0.f));

    if(Input->getIsKeyDown(GLFW_KEY_W))
        m_Entities[0]->SetPosition(glm::vec2(0.f, -5.f));

    if(Input->getIsKeyDown(GLFW_KEY_S))
        m_Entities[0]->SetPosition(glm::vec2(0.f, 5.f));
}

void Game::Render() {
    float timeStep = 1.f / 60.f;
    int32_t velocityIterations = 6;
    int32_t positionIterations = 6;
    this->world.Step(timeStep, velocityIterations, positionIterations);


    float my_color[4] = {m_Entities[0]->Color.x, m_Entities[1]->Color.y, m_Entities[2]->Color.x, 1.f};
    ImGui::Begin("Big Tool");
    ImGui::ColorEdit4("Color", my_color);
    ImGui::End();

    // Render all entities on the screen, do other stuff here too, like handle input and such
    ImGui::Begin("Entity information");
    int i = 0;
    for(auto entity: m_Entities) {
        m_Renderer->DrawSprite(*entity);
        this->ShowDebugInfo(*entity, ++i);
    }
    ImGui::End();
}

void Game::ShowDebugInfo(Entity entity, int i) {
    std::string label = "Entity " + std::to_string(i);
    if(ImGui::TreeNode(label.c_str()))
    {
        ImGui::Text("Position: (%f, %f)", entity.GetPosition().x, entity.GetPosition().y);
        ImGui::Text("Rotation: %f rads (%f deg)", entity.physicsBody->GetAngle(), glm::degrees(entity.physicsBody->GetAngle()));
        ImGui::Text("Velocity: (%f, %f)", entity.physicsBody->GetLinearVelocity().x, entity.physicsBody->GetLinearVelocity().y);

        b2AABB aabb = entity.physicsBody->GetFixtureList()->GetAABB(0);
        float x = aabb.lowerBound.x;
        float y = aabb.lowerBound.y;
        float width = aabb.upperBound.x - aabb.lowerBound.x;
        float height = aabb.upperBound.y - aabb.lowerBound.y;
        m_debugDraw.DrawRectangle(x, y, width, height);

        ImGui::TreePop();
    }
}
