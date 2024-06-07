#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "resource_manager.h"
#include "snake.h"

enum GameState
{
    GAME_ACTIVE,
    GAME_OVER
};
class Game
{
public:
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    Game(unsigned int width, unsigned int height);
    ~Game();
    void Init();
    void ProcessInput();
    void Update(const float *dt);
    void DrawObjects();
    void addFood();
private:
    Renderer* GameRenderer;
    float accumulatedTime = 0.0f;
    float stepTime = 0.15f;
    Snake::Direction nextMove;
    Snake *snake;
    GameObject *food;
};

#endif