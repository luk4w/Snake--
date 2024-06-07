#include "snake.h"

Snake::Snake(glm::vec2 pos, glm::vec3 color, Direction dir) : GameObject(pos, color), direction(dir) {}

// Overrided GameObject::Draw method
void Snake::Draw(Renderer &renderer)
{
    // Draw head
    renderer.Render(&Position, this->Color);
    // Draw tail
    for (auto &pos : tail)
    {
        renderer.Render(&pos, this->Color);
    }
}

void Snake::Move(Direction dir)
{
    UpdateTail();
    switch (dir)
    {
    case UP:
        this->Position.y -= step;
        break;
    case DOWN:
        this->Position.y += step;
        break;
    case LEFT:
        this->Position.x -= step;
        break;
    case RIGHT:
        this->Position.x += step;
        break;
    }
    this->direction = dir;
}

void Snake::Grow()
{
    switch (this->direction)
    {
    case UP:
        tail.push_back(glm::vec2(this->Position.x, this->Position.y + step));
        break;
    case DOWN:
        tail.push_back(glm::vec2(this->Position.x, this->Position.y - step));
        break;
    case LEFT:
        tail.push_back(glm::vec2(this->Position.x + step, this->Position.y));
        break;
    case RIGHT:
        tail.push_back(glm::vec2(this->Position.x - step, this->Position.y));
        break;
    }
}

void Snake::UpdateTail()
{
    glm::vec2 previous = this->Position;
    for (auto &pos : tail)
    {
        glm::vec2 temp = pos;
        pos = previous;
        previous = temp;
    }
}

bool Snake::isEating(GameObject &food)
{
    if (this->Position == food.Position)
    {
        return true;
    }
    return false;
}

bool Snake::isColliding(unsigned int width, unsigned int height)
{
    // Check if snake is out of bounds
    if (this->Position.x < 0 || this->Position.x >= width || this->Position.y < 0 || this->Position.y >= height)
    {
        return true;
    }

    // Check if snake is colliding with itself
    for (auto &pos : tail)
    {
        if (this->Position == pos)
        {
            return true;
        }
    }

    return false;
}

bool Snake::isCollidingFood(glm::vec2 foodPosition)
{
    if (this->Position == foodPosition)
    {
        return true;
    }

    for (auto &pos : tail)
    {
        if (pos == foodPosition)
        {
            return true;
        }
    }
    
    return false;
}

Snake::~Snake()
{
    tail.clear();
}
