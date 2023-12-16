#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "include/Errors.h"
#include "include/Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

static void glfw_error_callback(int error, const char* desc) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
}

int main() {
    int WIDTH = 1280, HEIGHT = 720;
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Renderer", nullptr, nullptr);
    if(!window) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Game game(WIDTH, HEIGHT, window);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::ShowDemoWindow();
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        game.Update();
        game.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
