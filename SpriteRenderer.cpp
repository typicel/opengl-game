//
// Created by tyler on 12/11/2023.
//

#include "include/SpriteRenderer.h"
#include "include/Errors.h"

SpriteRenderer::SpriteRenderer(Shader& shader) : shader(shader) {
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    GLCall(glDeleteVertexArrays(1, &this->quadVAO));
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);

    GLCall(glActiveTexture(GL_TEXTURE0));
    texture.Bind();

    GLCall(glBindVertexArray(this->quadVAO));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
    GLCall(glBindVertexArray(0));
}

void SpriteRenderer::initRenderData() {
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    VertexBuffer vbo(vertices, sizeof(vertices)); // implicitly calls glBindBuffer and glBufferData
    GLCall(glGenVertexArrays(1, &this->quadVAO));

    GLCall(glBindVertexArray(this->quadVAO));
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    vbo.Unbind();
    GLCall(glBindVertexArray(0));
}

