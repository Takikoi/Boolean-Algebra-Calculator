#include "ProgramState.hpp"

ProgramState::~ProgramState()
{
}

ProgramState::ProgramState(sf::RenderWindow* window_) 
    : State(window_)
{
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_)
{
    updateKeyBinds(dtTime_);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "A\n";
    }
    
}

void ProgramState::render(sf::RenderTarget* target_)
{

}

// ######################################################################## (Program functions)

void ProgramState::updateKeyBinds(const float& dtTime_)
{
    checkForQuit();
}

void ProgramState::endState()
{
    std::cout << "end";
}