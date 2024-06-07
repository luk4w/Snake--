#include "renderer.h"

Renderer::Renderer(Shader &shader)
{
    this->shader = shader;
    this->initRenderData();
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Renderer::Render( glm::vec2 * position, glm::vec3 color)
{
    const float size = 20.0f;;

    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(*position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size, 0.5f * size, 0.0f)); 
    // model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size, -0.5f * size, 0.0f));

    model = glm::scale(model, glm::vec3(size, size, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("uniformColor", color);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // First triangle 
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        // Second triangle
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}