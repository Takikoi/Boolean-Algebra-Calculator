#include "MainMenuState.hpp"

MainMenuState::~MainMenuState()
{
}

MainMenuState::MainMenuState()
    : State(window)
{
}

// ######################################################################## (Main Update & Render)

void MainMenuState::update(const float& dtTime_)
{

    
}

void MainMenuState::render(sf::RenderTarget* target_)
{

}

// ######################################################################## (Program functions)

void MainMenuState::updateInput(const float& dtTime_)
{
    checkForQuit();
}

void MainMenuState::endState()
{
    std::cout << "end";
}