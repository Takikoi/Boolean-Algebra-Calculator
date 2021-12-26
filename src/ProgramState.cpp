#include "ProgramState.hpp"

void ProgramState::initCellType()
{
    cellType.push_back(OR_GATE);
    cellType.push_back(AND_GATE);
    cellType.push_back(NOT_GATE);

    cellType.push_back(Gate_INPUT);
    cellType.push_back(Gate_INPUT_LEFT);
    cellType.push_back(Gate_INPUT_RIGHT);

    cellType.push_back(SIGNAL_A);
    cellType.push_back(SIGNAL_B);
    cellType.push_back(SIGNAL_C);
}

void ProgramState::initCells()
{
    // Allocate cells matrix
    cells = new Cell** [NUM_CELLS];
    for (short i = 0; i < NUM_CELLS; ++i)
        cells[i] = new Cell*[NUM_CELLS];

    // Create Cells matrix
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
    // Do not call delete window
    for (short i = 0; i < NUM_CELLS; ++i)
        for (short j = 0; j < NUM_CELLS; ++j)
            delete cells[i][j];
    
    for (short i = 0; i < NUM_CELLS; ++i)
        delete[] cells[i];
    delete[] cells;
}

ProgramState::ProgramState(sf::RenderWindow* window_) 
    : State(), window(window_)
{
    initCellType();
    initCells();
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);

    // Check Mouse Single-click

    // Set Cell type
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_))
            {
                static bool lock_click = false;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click == false)
                {
                    std::cout << "lmb-pressed" << std::endl; // usually this will show in a loop because is being pressed;
                    lock_click = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 

                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click == true)
                {
                    std::cout << "lmb-released" << std::endl;
                    lock_click = false; //unlock when the button(lmb) has been released.
                    if (iterator >= (cellType.size() - 1))
                        iterator = 0;
                    else iterator++;
                    std::cout << "Iter: " << iterator << std::endl;
                    cells[i][j]->update(dtTime_, mousePos_, cellType[iterator]);
                }
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