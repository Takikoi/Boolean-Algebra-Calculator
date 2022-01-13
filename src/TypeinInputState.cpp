#include "TypeinInputState.hpp"

void TypeinInputState::initUI()
{
    if (!font.loadFromFile("../fonts/Comfortaa-Medium.ttf"))
        std::cout << "Failed to load font\n";

    backGroundTexture.loadFromFile("../assets/TypeinBG.png");
    backGround.setTexture(backGroundTexture);

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
    str.append("- If the expression is not complete, the program will crash\n");
    str.append("- Enter MAXIMUM only 5 inputs.\n");
    str.append("- At 5 inputs, expression simplification is unfortunately unavailable.\n");
    str.append("\nEx: ((A+B')*C+D')\n\n");
    str.append("Press ENTER to view result");

    userManual.setString(str);
}

void TypeinInputState::initButtons()
{
    goBackButton = Button("", {76, 34}, 0, sf::Color::Transparent, sf::Color::Transparent);
    goBackButton.loadTextureFromFile("../assets/ToolbarButton.png", sf::IntRect(0, 0, 76, 34));
    goBackButton.setPosition({40, 40});
    // goBackButton.getSprite().setScale({1.5, 1.5});

    enterButton = Button("", {170, 69}, 0, sf::Color::Transparent, sf::Color::Transparent);
    enterButton.loadTextureFromFile("../assets/enterButton.png");
    enterButton.setPosition({1010, 253});
}

void TypeinInputState::initTextbox()
{
    textBox = Textbox(38, sf::Color(236, 234, 234), true);
    textBox.setFont(font);
    textBox.setPosition({100, (float)WINDOW_HEIGHT/5 + 70});
    textBox.setLimit(true, 45);
}

TypeinInputState::~TypeinInputState()
{
}

TypeinInputState::TypeinInputState(sf::RenderWindow* window_)
    : State(window_)
{
    initUI();
    initButtons();
    initTextbox();
}

void TypeinInputState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    static bool lock_click_left1 = false;
    if (enterButton.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == false)
        {
            lock_click_left1 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == true)
        {
            // When left click is released
            exit = true;
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
            // When left click is released
            exit = true;
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

void TypeinInputState::handleEvent(sf::Event& ev_)
{
    // When receive a text type in action from user
    textBox.typedOn(ev_);
}