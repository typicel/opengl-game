//
// Created by tyler on 12/15/2023.
//

#include "include/DebugDraw.h"
#include "include/ResourceManager.h"
#include "include/Errors.h"

DebugDraw::DebugDraw() {
    this->debugShader = ResourceManager::LoadShader(
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/shader.vert",
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/shader.frag",
            "debugShader"
    );

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1280), static_cast<float>(720), 0.0f, -1.0f, 1.0f); // FIX THIS LATER IT SHOULD BE LIKE THE ACTUAL WIDTH AND HEIGHT
    this->debugShader.Use();
    this->debugShader.SetMatrix4("projection", projection);
}

void DebugDraw::DrawRectangle(float x, float y, float width, float height) {

    float vertices[] = {
            1.f, 0.f, 0.f,              // top right
            1.f, 1.f, 0.f,     // bottom right
            0.f, 1.f, 0.f,             // bottom left
            0.f, 0.f, 0.f                      // top left
    };

    unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    unsigned int VBO, VAO, EBO;
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glGenVertexArrays(1, &VAO));

    GLCall(glBindVertexArray(VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    this->debugShader.Use();
    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f)); // Translate
    model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f)); // so that movements occurs at center of sprite
    model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f)); // Scale

    this->debugShader.SetMatrix4("model", model);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLCall(glBindVertexArray(VAO));
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void DebugDraw::DrawLine(float pos, float len) {

}
