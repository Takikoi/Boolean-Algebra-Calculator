#include "TypeinInputState.hpp"

void TypeinInputState::initStuff()
{
    if (!font.loadFromFile("../fonts/Orbitron-Medium.ttf"))
        std::cout << "Failed to load font\n";

    backGroundTexture.loadFromFile("../assets/TypeinBG.png");
    backGround.setTexture(backGroundTexture);

    textBox = Textbox(38, sf::Color(236, 234, 234), true);
    textBox.setFont(font);
    textBox.setPosition({100, (float)WINDOW_HEIGHT/5 + 70});
    textBox.setLimit(true, 45);

    title.setFont(font);
    title.setCharacterSize(48);
    title.setColor(sf::Color(78, 78, 78));
    title.setPosition({100, (float)WINDOW_HEIGHT/5 - 30});
    title.setString("Enter Expression:");

    userManual.setFont(font);
    userManual.setCharacterSize(32);
    userManual.setColor(sf::Color(78, 78, 78));
    userManual.setPosition({90, (float)WINDOW_HEIGHT/5 + 170});
    std::string str = "";
    str.append("Syntax Rules:\n");
    str.append("- OR gate: operator +\n");
    str.append("- AND gate: operator *\n");
    str.append("- NOT gate: operator '\n");
    str.append("- There must be no SPACE between charaters\n");
    str.append("- If the expression is not complete, the program will not work\n");
    str.append("Ex: ((A+B')*C+D')\n\n");
    str.append("Press ENTER to proceed");

    userManual.setString(str);

    goBackButton = Button("", {76, 34}, 0, sf::Color::Transparent, sf::Color::Transparent);
    goBackButton.loadTextureFromFile("../assets/ToolbarButton.png", sf::IntRect(0, 0, 76, 34));
    goBackButton.setPosition({40, 40});
    // goBackButton.getSprite().setScale({1.5, 1.5});

    enterButton = Button("", {76, 34}, 0, sf::Color::Transparent, sf::Color::Transparent);
    enterButton.loadTextureFromFile("../assets/enterButton.png");
    enterButton.setPosition({1010, 253});
}

TypeinInputState::~TypeinInputState()
{
}

TypeinInputState::TypeinInputState(sf::RenderWindow* window_)
    : State(), window(window_)
{
    initStuff();
}

void TypeinInputState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        std::cout << textBox.getText();
    }

    static bool lock_click_left1 = false;

    if (enterButton.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == false)
        {
            lock_click_left1 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == true)
        {
            quit = true;
            exitFlag = GO_TO_OUTPUT;
            lock_click_left1 = false;
            exp = textBox.getText();
        }
    }

    static bool lock_click_left2 = false;
    if (goBackButton.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left2 == false)
        {
            lock_click_left2 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left2 == true)
        {
            quit = true;
            exitFlag = GO_TO_MENU;
            lock_click_left2 = false;
            
        }
    }
}

void TypeinInputState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
    textBox.render(window);
    window->draw(title);
    window->draw(userManual);
    goBackButton.render(window);
    enterButton.render(window);
}

void TypeinInputState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
}

void TypeinInputState::updateMousePos(const sf::Vector2i& mousePos_)
{}

void TypeinInputState::handleEvent(sf::Event& ev_)
{
    textBox.typedOn(ev_);
}