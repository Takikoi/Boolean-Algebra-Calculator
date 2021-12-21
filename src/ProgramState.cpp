#include "ProgramState.hpp"

ProgramState::~ProgramState()
{
    delete window;
}

ProgramState::ProgramState(sf::RenderWindow* window_) 
    : State(window_)
{
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);
    logicGate.update(dtTime_, mousePos_);
}

void ProgramState::render(sf::RenderTarget* target_)
{
    if (!target_)
        target_ = window;
    logicGate.render(target_);
}

// ######################################################################## (Program functions)

void ProgramState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    checkForQuit();
    updateMousePos(mousePos_);
}

void ProgramState::updateMousePos(const sf::Vector2i& mousePos_) {
    mousePos = mousePos_;
}