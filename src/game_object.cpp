#include "game_object.h"

GameObject::GameObject(glm::vec2 pos, glm::vec3 color)
    : Position(pos), Color(color) {}

void GameObject::Draw(Renderer &renderer)
{
    renderer.Render(&Position, this->Color);
}