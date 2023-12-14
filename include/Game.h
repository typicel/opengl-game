#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include <glfw/glfw3.h>
#include <box2d/b2_world.h>

// std
#include <vector>
#include <memory>

class Game {
public:
    Game(int screen_width, int screen_height, GLFWwindow* window);

    void Render();
    void Update();

private:
    b2World world;

    InputManager* Input;
    GLFWwindow* m_Window;
    std::vector<Entity*> m_Entities;
    std::shared_ptr<SpriteRenderer> m_Renderer;
};
