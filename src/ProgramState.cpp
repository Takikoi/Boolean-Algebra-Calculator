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
    player.update(dtTime_);
    
}

void ProgramState::render(sf::RenderTarget* target_)
{
    player.render(target_);
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