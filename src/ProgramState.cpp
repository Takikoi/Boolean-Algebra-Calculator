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
    std::cout << "yello\n";
}

void ProgramState::render(sf::RenderTarget* target_)
{

}

// ######################################################################## (Program functions)

void ProgramState::endState()
{}