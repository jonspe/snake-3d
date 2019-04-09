#include "gameengine.hh"

GameEngine::GameEngine(): snake_(nullptr)
{
}

void GameEngine::gameLoop()
{
    //timer.start();
}

void GameEngine::update()
{
}

void GameEngine::render()
{
    snake_->render();
}
