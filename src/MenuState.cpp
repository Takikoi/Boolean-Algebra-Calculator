#include "MenuState.hpp"

void MenuState::initButtons()
{
    if (!font.loadFromFile("../fonts/Orbitron-Medium.ttf"))
        std::cout << "Failed to load font\n";

    typeInOption = Button("Type in", {200, 100}, 24, sf::Color::Black, sf:: Color::White);
    typeInOption.setFont(font);
    typeInOption.setPosition({(float)WINDOW_WIDTH/2 - 200/2, 500});

    graphicInputOption = Button("Graphic", {200, 100}, 24, sf::Color::Black, sf:: Color::White);
    graphicInputOption.setFont(font);
    graphicInputOption.setPosition({(float)WINDOW_WIDTH/2 - 200/2, 650});

    title.setFont(font);
    title.setCharacterSize(70);
    title.setPosition({200, 200});
    title.setColor(sf::Color(78, 78, 78));
    title.setStyle(sf::Text::Bold);
    title.setString("BOOLEAN  ALGEBRA\n     CALCULATOR");
    
    if (!backGroundTexture.loadFromFile("../assets/MenuBG.png"))
        std::cout << "Failed to load texture\n";
    backGround.setTexture(backGroundTexture);
}

MenuState::~MenuState()
{
}

MenuState::MenuState()
{
}

MenuState::MenuState(sf::RenderWindow* window_)
    : State(), window(window_)
{
    initButtons();
}

// ######################################################################## (Main Update & Render)

void MenuState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    static bool lock_click_left1 = false;
    if (graphicInputOption.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == false)
        {
            lock_click_left1 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == true)
        {
            lock_click_left1 = false;
            exitFlag = GO_TO_GRAPHIC;
            quit = true;
        }
    }

    static bool lock_click_left2 = false;
    if (typeInOption.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left2 == false)
        {
            lock_click_left2 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left2 == true)
        {
            lock_click_left2 = false;
            exitFlag = GO_TO_TYPEIN;
            quit = true;
        }
    }
}

void MenuState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
    typeInOption.render(window);
    graphicInputOption.render(window);
    window->draw(title);
}

// ######################################################################## (Program functions)

void MenuState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{

}

void MenuState::updateMousePos(const sf::Vector2i& mousePos_)
{

}

void MenuState::handleEvent(sf::Event& ev_)
{}