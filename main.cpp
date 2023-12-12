
#include <iostream>
#include "include/VertexBuffer.h"
#include "include/IndexBuffer.h"
#include "include/SpriteRenderer.h"
#include "include/Shader.h"
#include "include/ResourceManager.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "include/Errors.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

int main() {
    int WIDTH = 800, HEIGHT= 600;
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", nullptr, nullptr);
    if(!window){
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();


    ResourceManager* manager;
    Shader sprite_shader = ResourceManager::LoadShader("C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.vert", "C:/Users/tyler/Projects/renderer/Assets/Shaders/sprite.frag", "sprite_shader");
    Texture2D nugget_texture = ResourceManager::LoadTexture("C:/Users/tyler/Projects/renderer/Assets/Sprites/nugglet.png", "nugglet", true);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);
    sprite_shader.Use();
    sprite_shader.SetInteger("image", 0);
    sprite_shader.SetMatrix4("projection", projection);

    auto renderer = new SpriteRenderer(sprite_shader);

    while(!glfwWindowShouldClose(window))
    {
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        renderer->DrawSprite(nugget_texture, glm::vec2(200.0f, 200.0f), glm::vec2(400.0f, 400.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
