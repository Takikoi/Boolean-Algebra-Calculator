#include "TypeinInputState.hpp"

void TypeinInputState::initStuff()
{
    if (!font.loadFromFile("../fonts/Orbitron-Medium.ttf"))
        std::cout << "Failed to load font\n";

    backGroundTexture.loadFromFile("../assets/TypeinBG.png");
    backGround.setTexture(backGroundTexture);

    textBox = Textbox(38, sf::Color(236, 234, 234), true);
    textBox.setFont(font);
    textBox.setPosition({100, (float)WINDOW_HEIGHT/5 + 100});
    textBox.setLimit(true, 45);

    title.setFont(font);
    title.setCharacterSize(48);
    title.setColor(sf::Color(78, 78, 78));
    title.setPosition({100, (float)WINDOW_HEIGHT/5});
    title.setString("Enter Expression:");

    userManual.setFont(font);
    userManual.setCharacterSize(32);
    userManual.setColor(sf::Color(78, 78, 78));
    userManual.setPosition({90, (float)WINDOW_HEIGHT/5 + 200});
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
}

void TypeinInputState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
    textBox.render(window);
    window->draw(title);
    window->draw(userManual);
}

void TypeinInputState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void TypeinInputState::updateMousePos(const sf::Vector2i& mousePos_)
{}

void TypeinInputState::handleEvent(sf::Event& ev_)
{
    textBox.typedOn(ev_);
}