#pragma once

#include "Entity.h"
#include "SpriteRenderer.h"
#include <vector>
#include <memory>
#include <glfw/glfw3.h>

class Game {
public:
    Game(int screen_width, int screen_height);
    void Render();
    void Update();

private:
    std::vector<std::shared_ptr<Entity>> m_Entities;
    std::shared_ptr<SpriteRenderer> m_Renderer;
};
