#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "game_object.h"

class Snake : public GameObject
{
public:
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Direction direction;
    Snake(glm::vec2 position, glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f), Direction direction = RIGHT);
    ~Snake();
    void Grow();
    void Draw(Renderer &renderer) override;
    void Move(Direction dir);
    bool isColliding(unsigned int width, unsigned int height);
    void UpdateTail();
    bool isEating(GameObject &food);
    bool isCollidingFood(glm::vec2 foodPosition);
    size_t GetSize() { return tail.size() + 1; }

private:
    const float step = 20.0f;
    std::vector<glm::vec2> tail;
};

#endif