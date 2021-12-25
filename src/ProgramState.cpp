#include "ProgramState.hpp"

void ProgramState::initCells()
{
    // Allocate cells matrix
    cells = new Cell** [NUM_CELLS];
    for (short i = 0; i < NUM_CELLS; ++i)
        cells[i] = new Cell*[NUM_CELLS];

    // Init Cells field
    short x(0), y(0);
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            cells[i][j] = new Cell(sf::Vector2f(x, y));
            x += CELL_SIZE;
        }
        x = 0;
        y += CELL_SIZE;
    }
}

ProgramState::~ProgramState()
{
    for (short i = 0; i < NUM_CELLS; ++i)
        for (short j = 0; j < NUM_CELLS; ++j)
            delete cells[i][j];
    
    for (short i = 0; i < NUM_CELLS; ++i)
        delete[] cells[i];
    delete[] cells;
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
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                cells[i][j]->update(dtTime_, mousePos_, "Signal A");
            }
            else
            {
                cells[i][j]->update(dtTime_, mousePos_, "Signal C");
            }
        }
    }
}

void ProgramState::render(sf::RenderTarget* target_)
{
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            cells[i][j]->render(target_);
        }
    }
    //cells[0][0]->render(target_);
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