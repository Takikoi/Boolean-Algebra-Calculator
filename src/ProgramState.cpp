#include "ProgramState.hpp"

void ProgramState::initExpElement()
{
    expressionElement.emplace(EMPTY_CELL, "");

    expressionElement.emplace(OR_GATE , "+");
    expressionElement.emplace(AND_GATE, "*");
    expressionElement.emplace(NOT_GATE, "!");

    expressionElement.emplace(GATE_INPUT       , "");
    expressionElement.emplace(WIRE_CORNER_LEFT , "");
    expressionElement.emplace(WIRE_CORNER_RIGHT, "");
    expressionElement.emplace(WIRE_HORIZONTAL  , "");
    expressionElement.emplace(WIRE_VERTICAL    , "");

    expressionElement.emplace(SIGNAL_IN_A, "A");
    expressionElement.emplace(SIGNAL_IN_B, "B");
    expressionElement.emplace(SIGNAL_IN_C, "C");
    expressionElement.emplace(SIGNAL_IN_D, "D");
    expressionElement.emplace(SIGNAL_IN_E, "E");
    expressionElement.emplace(SIGNAL_IN_F, "F");
    expressionElement.emplace(SIGNAL_IN_G, "G");

    expressionElement.emplace(SIGNAL_OUT_1, "x");
    expressionElement.emplace(SIGNAL_OUT_2, "y");
    expressionElement.emplace(SIGNAL_OUT_3, "z");
}

void ProgramState::initCellType()
{
    cellType.push_back(EMPTY_CELL);

    cellType.push_back(OR_GATE);
    cellType.push_back(AND_GATE);
    cellType.push_back(NOT_GATE);

    cellType.push_back(GATE_INPUT);
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
    initExpElement();
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);
    
    // Check Mouse Single-click
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_))
            {
                //std::cout << "(" << i << ", " << j << ")\n";
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
    static bool lock_enter = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && lock_enter == false)
    {
        lock_enter = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && lock_enter == true)
    {
        std::cout << "EXP: " << generateExpression() << "\n";
        lock_enter = false; //unlock when the button(lmb) has been released.
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

std::string ProgramState::generateExpression()
{
    short i, j;
    for (j = NUM_CELLS - 1; j >= 0; --j)
        for (i = 0; i < NUM_CELLS; ++i)
            if (cells[i][j]->getCurrentType() == SIGNAL_OUT_1)
            {
                std::cout << "Found output\n";
                goto endLoop;
            }
                
    endLoop:
    
    return exp2(i, j - 1, 1);
}

std::string ProgramState::exp(short x_, short y_, short flag)
{
    std::string result = "";
    if (flag == 0)
    {
        for (short j = y_ - 2; j >= 0; --j)
        {
            for (short i = x_ - 1; i >= 0; --i)
            {
                switch (cells[i][j]->getCurrentType())
                {
                case OR_GATE:
                    result = "( + )";
                    std::cout << "(x, y): " << i << ", " << j << "\n";
                    result.replace(1, 1, exp(i, j, 1));
                    result.replace(result.size() - 2, 1, exp(i, j, 0));
                    goto endLoop1;
                    break;
                
                case AND_GATE:
                    result = " * ";
                    std::cout << "(x, y): " << i << ", " << j << "\n";
                    result.replace(0, 1, exp(i, j, 0));
                    goto endLoop1;
                    break;

                default:
                    break;
                }
            }
        }
        endLoop1:
        return result;
    }
    else if (flag == 1)
    {
        for (short j = y_ - 1; j >= 0; --j)
        {
            for (short i = x_ + 1; i < NUM_CELLS; ++i)
            {
                switch (cells[i][j]->getCurrentType())
                {
                case OR_GATE:
                    result = "( + )";
                    std::cout << "(x, y): " << i << ", " << j << "\n";
                    result.replace(1, 1, exp(i, j, 1));
                    result.replace(result.size() - 2, 1, exp(i, j, 0));
                    goto endLoop2;
                    break;
                
                case AND_GATE:
                    result = " * ";
                    std::cout << "(x, y): " << i << ", " << j << "\n";
                    result.replace(0, 1, exp(i, j, 0));
                    goto endLoop2;
                    break;

                default:
                    break;
                }
            }
        }
        endLoop2:
        return result;
    }
}

std::string ProgramState::exp2(short x_, short y_, unsigned char previousType_, bool up)
{
    std::string result = "";
    switch (cells[x_][y_]->getCurrentType())
    {
    case OR_GATE:
        result = "( + )";
        result.replace(1, 1, exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType(), 1));
        result.replace(result.size() - 2, 1, exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType(), 0));
        break;
    
    case AND_GATE:
        result = " * ";
        result.replace(0, 1, exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType(), 1));
        result.replace(result.size() - 1, 1, exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType(), 0));
        break;

    case GATE_INPUT:
        result = (up ? exp2(x_ - 1, y_, cells[x_][y_]->getCurrentType()) : exp2(x_ + 1, y_, cells[x_][y_]->getCurrentType()));
        break;

    case WIRE_CORNER_LEFT:
        result = exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType());
        break;

    case WIRE_CORNER_RIGHT:
        result = exp2(x_, y_ - 1, cells[x_][y_]->getCurrentType());
        break;

    case SIGNAL_IN_A:
        result = "A";
        break;
    default:
        break;
    }
    return result;
}