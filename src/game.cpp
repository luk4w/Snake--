#include "game.h"

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Width(width), Height(height)
{
}

Game::~Game()
{
    delete snake;
    delete GameRenderer;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/vertex.glsl", "shaders/fragment.glsl", nullptr, "default");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("default").Use();
    ResourceManager::GetShader("default").SetMatrix4("projection", projection);
    GameRenderer = new Renderer(ResourceManager::GetShader("default"));
    snake = new Snake(glm::vec2(20.0f, 20.0f));
    nextMove = Snake::RIGHT;
}

void Game::addFood()
{
    int x = (rand() % Width / 20) * 20;
    int y = (rand() % Height / 20) * 20;
    food = new GameObject(glm::vec2(x, y), glm::vec3(1.0f, 0.0f, 0.0f));

    while (snake->isCollidingFood(food->Position))
    {
        if (snake->GetSize() == Width / 20 * Height / 20)
        {
            State = GAME_OVER;
            printf("You Win\n");
            exit(0);
        }
        addFood();
    }
}

void Game::Update(const float *dt)
{
    accumulatedTime += *dt;
    ProcessInput();
    if (accumulatedTime >= stepTime)
    {
        snake->Move(nextMove);
        accumulatedTime = 0.0f;
    }

    if (snake->isColliding(Width, Height))
    {
        State = GAME_OVER;
        printf("Game Over\n");
        exit(0);
    }

    if (food != nullptr && snake->isEating(*food))
    {
        snake->Grow();
        delete food;
        food = nullptr;
    }
    DrawObjects();
}

void Game::ProcessInput()
{
    if (this->State == GAME_ACTIVE)
    {
        if (this->Keys[GLFW_KEY_A] && nextMove != Snake::LEFT && snake->direction != Snake::RIGHT)
        {
            nextMove = Snake::LEFT;
        }
        else if (this->Keys[GLFW_KEY_D] && nextMove != Snake::RIGHT && snake->direction != Snake::LEFT)
        {
            nextMove= Snake::RIGHT;
        }
        else if (this->Keys[GLFW_KEY_W] && nextMove != Snake::UP && snake->direction != Snake::DOWN)
        {
            nextMove = Snake::UP;
        }
        else if (this->Keys[GLFW_KEY_S] && nextMove != Snake::DOWN && snake->direction != Snake::UP)
        {
            nextMove = Snake::DOWN;
        }
    }
}

void Game::DrawObjects()
{
    snake->Draw(*GameRenderer);
    if (food != nullptr)
    {
        food->Draw(*GameRenderer);
    }
    else
    {
        addFood();
    }
}