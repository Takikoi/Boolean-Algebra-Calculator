#include "ProgramState.hpp"

void ProgramState::initCells()
{
    int f = 0;
    for (size_t i = 0; i < NUM_CELLS; i++)
    {
        cells.push_back(Cell(sf::Vector2f(f, 0.f)));
        f += 125;
    }
    
}

ProgramState::~ProgramState()
{
}

ProgramState::ProgramState() 
    : State()
{
    initCells();
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);
    

}

void ProgramState::render(sf::RenderTarget* target_)
{
    
    for (Cell& iter : cells)
    {
        iter.render(target_);
    }

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