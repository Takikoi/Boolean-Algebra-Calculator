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
    cells = new Cell** [CELL_FIELD_DIM_X];
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
        cells[i] = new Cell*[CELL_FIELD_DIM_Y];

    // Create Cells matrix
    short x(0), y(WINDOW_HEIGHT - CELL_SIZE * CELL_FIELD_DIM_Y);
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            cells[i][j] = new Cell(sf::Vector2f(x, y));
            y += CELL_SIZE;
        }
        y = WINDOW_HEIGHT - CELL_SIZE * CELL_FIELD_DIM_Y;
        x += CELL_SIZE;
    }
}

void ProgramState::initTexture()
{
    UI_barTexture.loadFromFile("../assets/UI.png");
    UI_bar.setTexture(UI_barTexture);
    
    backButtonTexture.loadFromFile("../assets/ToolbarButton.png");
    backButton.setTexture(backButtonTexture);

    backButton.setTextureRect(sf::IntRect(0, 0, 76, 34));
    backButton.setPosition(16, 16);
}

ProgramState::~ProgramState()
{
    // Do not call delete window
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
            delete cells[i][j];
    
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
        delete[] cells[i];
    delete[] cells;
}

ProgramState::ProgramState(sf::RenderWindow* window_) 
    : State(), window(window_)
{
    // Init list will init in the order of object in class declaration not of the list
    initCellType();
    initCells();
    initExpElement();
    initTexture();

    // expression must be init after cells
    expression = BoolExpression(cells);
    testCell = Cell(sf::Vector2f(100, 50));
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);
    
    // Check Mouse Single-click
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_))
            {
                //std::cout << "(" << i << ", " << j << ")\n";
                static bool lock_click_left = false;
                static bool lock_click_right = false;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == false)
                {
                    //std::cout << "lmb-pressed" << std::endl; // usually this will show in a loop because is being pressed;
                    lock_click_left = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 

                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == true)
                {
                    //std::cout << "lmb-released" << std::endl;
                    lock_click_left = false; //unlock when the button(lmb) has been released.

                    cells[i][j]->changeToNextType();
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == false)
                {
                    //std::cout << "rmb-pressed" << std::endl; // usually this will show in a loop because is being pressed;
                    lock_click_right = true; //And now, after all your code, this will lock the loop and not print "lmb" in a x held time. 

                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == true)
                {
                    //std::cout << "rmb-released" << std::endl;
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
        std::cout << "EXP: " << expression.getExpression() << "\n";
        lock_enter = false; //unlock when the button(lmb) has been released.
    }
}

void ProgramState::render(sf::RenderTarget* target_)
{
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            cells[i][j]->render(target_);
        }
    }
    target_->draw(UI_bar);
    // target_->draw(backButton);
    //testCell.render(target_);
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
