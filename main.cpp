#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "include/Errors.h"
#include "include/Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

int main() {
    int WIDTH = 1920, HEIGHT= 1080;
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    Game game(WIDTH, HEIGHT, window);
    while(!glfwWindowShouldClose(window)) {
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        game.Update();
        game.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
