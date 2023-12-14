#include "include/SpriteRenderer.h"
#include "include/Errors.h"

SpriteRenderer::SpriteRenderer(const char* vShaderFile, const char* fShaderFile) {
    this->shader = ResourceManager::LoadShader(vShaderFile, fShaderFile, "sprite_shader");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f); // FIX THIS LATER IT SHOULD BE LIKE THE ACTUAL WIDTH AND HEIGHT
    this->shader.Use();
    this->shader.SetInteger("image", 0);
    this->shader.SetMatrix4("projection", projection);

    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    GLCall(glDeleteVertexArrays(1, &this->quadVAO));
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {

    this->shader.Use();

    // The model matrix defines all transformations on this sprite
    // Should first translate, then rotate, then scale (reverse in code because multiplication is right -> left
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f)); // Translate
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // so that movements occurs at center of sprite
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f)); // Scale

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

