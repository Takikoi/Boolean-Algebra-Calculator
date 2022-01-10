#include "GraphicInputState.hpp"

void GraphicInputState::initCells()
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

void GraphicInputState::initTexture()
{
    UI_barTexture.loadFromFile("../assets/UI.png");
    UI_bar.setTexture(UI_barTexture);
    UI_bar.setPosition(0, 0);

    goBackButton = Button("", {76, 34}, 0, sf::Color::Transparent, sf::Color::Transparent);
    goBackButton.loadTextureFromFile("../assets/ToolbarButton.png", sf::IntRect(0, 0, 76, 34));
    goBackButton.setPosition({12, 15});

    goForwardButton = Button("", {76, 34}, 0, sf::Color::Transparent, sf::Color::Transparent);
    goForwardButton.loadTextureFromFile("../assets/ToolbarButton.png", sf::IntRect(0, 34, 76, 34));
    goForwardButton.setPosition({100, 15});
}

void GraphicInputState::initText()
{
    if (!font.loadFromFile("../fonts/Orbitron-Medium.ttf"))
        std::cout << "Failed to load font\n";
    
    UI_log.setFont(font);
    UI_log.setCharacterSize(24);
    UI_log.setColor(sf::Color(236, 234, 234));
    UI_log.setPosition(400, 18);
    UI_log.setString("Hello there");
}

GraphicInputState::~GraphicInputState()
{
    // Do not call delete window
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
            delete cells[i][j];
    
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
        delete[] cells[i];
    delete[] cells;
}

GraphicInputState::GraphicInputState(sf::RenderWindow* window_) 
    : State(), window(window_)
{
    // Init list will init in the order of object in class declaration not of the list
    initCells();
    initTexture();
    initText();

    // expression must be init after cells
    expression = BoolExpression(cells);
}

// ######################################################################## (Main Update & Render)

void GraphicInputState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);

    // Check Mouse Single-click
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            if (cells[i][j]->cursorDetected(mousePos_))
            {
                static bool lock_click_left = false;
                static bool lock_click_right = false;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == false)
                {
                    lock_click_left = true;
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left == true)
                {
                    lock_click_left = false;
                    cells[i][j]->changeToNextType();
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == false)
                {
                    lock_click_right = true;
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && lock_click_right == true)
                {
                    lock_click_right = false;
                    cells[i][j]->changeToPreviousType();
                }
            }
        }
    }

    static bool lock_enter = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && lock_enter == false)
    {
        lock_enter = true;
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && lock_enter == true)
    {
        exp = expression.getExpression();
        UI_log.setString(exp);
        lock_enter = false;
    }

    static bool lock_goBack = false;
    if (goBackButton.cursorDetected(mousePos_))
    {   
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_goBack == false)
        {
            lock_goBack = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_goBack == true)
        {
            lock_goBack = false;
            exitFlag = GO_TO_MENU;
            UI_log.setString("goto menu");
            exitFlag = GO_TO_MENU;
            quit = true;
        }
    }

    static bool lock_goForward = false;
    if (goForwardButton.cursorDetected(mousePos_))
    {   
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_goForward == false)
        {
            lock_goForward = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_goForward == true)
        {
            lock_goForward = false;
            quit = true;
            exitFlag = GO_TO_OUTPUT;
            UI_log.setString("goto output");
        }
    }
}

void GraphicInputState::render(sf::RenderTarget* target_)
{
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            cells[i][j]->render(window);
        }
    }
    window->draw(UI_bar);
    window->draw(UI_log);
    goBackButton.render(window);
    goForwardButton.render(window);
}

// ######################################################################## (Program functions)

void GraphicInputState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    checkForQuit();
    updateMousePos(mousePos_);
}

void GraphicInputState::updateMousePos(const sf::Vector2i& mousePos_) {
    mousePos = mousePos_;
}

void GraphicInputState::handleEvent(sf::Event& ev_)
{
}
