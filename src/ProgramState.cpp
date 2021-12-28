#include "ProgramState.hpp"

void ProgramState::initCellType()
{
    cellType.push_back(EMPTY_CELL);

    cellType.push_back(OR_GATE);
    cellType.push_back(AND_GATE);
    cellType.push_back(NOT_GATE);

    cellType.push_back(Gate_INPUT);
    cellType.push_back(WIRE_CORNER_LEFT);
    cellType.push_back(WIRE_CORNER_RIGHT);

    cellType.push_back(SIGNAL_IN_A);
    cellType.push_back(SIGNAL_IN_B);
    cellType.push_back(SIGNAL_IN_C);
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
    static bool lock_enter = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && lock_enter == false)
    {
        lock_enter = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && lock_enter == true)
    {
        generateExpression();
        lock_enter = false; //unlock when the button(lmb) has been released.
    }
    // Check Mouse Single-click
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_))
            {
                std::cout << "(" << i << ", " << j << ")\n";
                static bool lock_click_left = false;
                static bool lock_click_right = false;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == false)
                {
                    std::cout << "lmb-pressed" << std::endl; // usually this will show in a loop because is being pressed;
                    lock_click_left = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 

                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == true)
                {
                    std::cout << "lmb-released" << std::endl;
                    lock_click_left = false; //unlock when the button(lmb) has been released.

                    cells[i][j]->changeToNextType();
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == false)
                {
                    std::cout << "rmb-pressed" << std::endl; // usually this will show in a loop because is being pressed;
                    lock_click_right = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 

                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == true)
                {
                    std::cout << "rmb-released" << std::endl;
                    lock_click_right = false; //unlock when the button(lmb) has been released.

                    cells[i][j]->changeToPreviousType();
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

void ProgramState::generateExpression()
{
    short i, j;
    for (j = NUM_CELLS - 1; j >= 0; --j)
        for (i = 0; i < NUM_CELLS; ++i)
            if (cells[i][j]->getCurrentType() == SIGNAL_OUT_1)
                goto endLoop;
    endLoop:
    checkUp(i, j);
    checkDown(i, j);
}

void ProgramState::checkUp(short& x_, short& y_)
{
    for (short j = y_ - 1; j >= 0; --j)
    {
        for (short i = x_ - 1; i >= 0; --i)
        {
            switch (cells[i][j]->getCurrentType())
            {
            case OR_GATE:
                boolExpression.insert(0, expressi)
                checkUp(i, j);
                checkDown(i, j);
                break;
            
            default:
                break;
            }
        }
    }
}

void ProgramState::checkDown(short& x_, short& y_)
{

}