#include "include/DebugDraw.h"
#include "include/ResourceManager.h"
#include "include/Errors.h"
#include "include/VertexBuffer.h"

DebugDraw::DebugDraw(int width, int height) {
    this->debugShader = ResourceManager::LoadShader(
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/debug.vert",
            "C:/Users/tyler/Projects/renderer/Assets/Shaders/debug.frag",
            "debugShader"
    );

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f); // FIX THIS LATER IT SHOULD BE LIKE THE ACTUAL WIDTH AND HEIGHT
    this->debugShader.Use();
    this->debugShader.SetMatrix4("projection", projection);
}

void DebugDraw::DrawRectangle(float x, float y, float width, float height) {

    float vertices[] = {
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
    };

    VertexBuffer verts(vertices, sizeof(vertices));

    unsigned int VAO;
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    this->debugShader.Use();

    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f)); // Translate
    model = glm::scale(model, glm::vec3(width, height, 1.0f)); // Scale

    this->debugShader.SetMatrix4("model", model);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    GLCall(glBindVertexArray(VAO));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDeleteVertexArrays(1, &VAO);
    verts.Unbind();
}

void DebugDraw::DrawLine(float pos, float len) {

}
