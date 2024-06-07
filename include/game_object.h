#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "renderer.h"

class GameObject
{
public:
    GameObject(glm::vec2 pos, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f));
    virtual void Draw(Renderer &renderer);
    glm::vec2 Position;
    glm::vec3 Color;
};

#endif