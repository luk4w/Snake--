#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer
{
public:
    Renderer(Shader &shader);
    ~Renderer();
    void Render(glm::vec2 * position, glm::vec3 color);
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

#endif