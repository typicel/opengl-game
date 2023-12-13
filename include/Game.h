#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include "InputManager.h"
#include <glfw/glfw3.h>

// std
#include <vector>
#include <memory>

class Game {
public:
    Game(int screen_width, int screen_height, GLFWwindow* window);

    void Render();
    void Update();

private:
    InputManager* Input;
    GLFWwindow* m_Window;
    std::vector<std::shared_ptr<Entity>> m_Entities;
    std::shared_ptr<SpriteRenderer> m_Renderer;
};
