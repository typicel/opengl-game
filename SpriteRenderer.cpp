#include "include/SpriteRenderer.h"
#include "include/Errors.h"

SpriteRenderer::SpriteRenderer(const char* vShaderFile, const char* fShaderFile, int width, int height) {
    this->shader = ResourceManager::LoadShader(vShaderFile, fShaderFile, "sprite_shader");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f); // FIX THIS LATER IT SHOULD BE LIKE THE ACTUAL WIDTH AND HEIGHT
    this->shader.Use();
    this->shader.SetInteger("image", 0);
    this->shader.SetMatrix4("projection", projection);

    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    GLCall(glDeleteVertexArrays(1, &this->quadVAO));
}

void SpriteRenderer::DrawSprite(const Entity &entity) {

    this->shader.Use();

    auto body = entity.physicsBody;
    // The model matrix defines all transformations on this sprite
    // Should first translate, then rotate, then scale (reverse in code because multiplication is right -> left
    glm::mat4 model = glm::mat4(1.0f);
    float x = body->GetPosition().x - (entity.Size.x/2);
    float y = body->GetPosition().y - (entity.Size.y/2);

//    float x = body->GetPosition().x;
//    float y = body->GetPosition().y;
    model = glm::translate(model, glm::vec3(x, y, 0.0f)); // Translate
    model = glm::translate(model, glm::vec3(0.5f * entity.Size.x, 0.5f * entity.Size.y, 0.0f)); // so that rotation occurs at center of sprite
    model = glm::rotate(model, glm::radians(body->GetTransform().q.GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate
    model = glm::translate(model, glm::vec3(-0.5f * entity.Size.x, -0.5f * entity.Size.y, 0.0f));
    model = glm::scale(model, glm::vec3(entity.Size, 1.0f)); // Scale

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", entity.Color);

    GLCall(glActiveTexture(GL_TEXTURE0));
    entity.Sprite.Bind();

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

