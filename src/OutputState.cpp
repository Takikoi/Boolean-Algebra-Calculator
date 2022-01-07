#include "OutputState.hpp"

void OutputState::initStuff()
{
    if (!backGroundTexture.loadFromFile("../assets/OutputBG.png"))
        std::cout << "Failed to load texture\n";
    backGround.setTexture(backGroundTexture);

    if (!font.loadFromFile("../fonts/Orbitron-Medium.ttf"))
        std::cout << "Failed to load font\n";
    
    sopTxt.setFont(font);
    sopTxt.setCharacterSize(64);
    sopTxt.setColor(sf::Color(78, 78, 78));
    sopTxt.setPosition({0, 0});

    simplifiedExpTxt.setFont(font);
    simplifiedExpTxt.setCharacterSize(64);
    simplifiedExpTxt.setColor(sf::Color(78, 78, 78));
    simplifiedExpTxt.setPosition({100, 100});
}

OutputState::~OutputState()
{
}

OutputState::OutputState()
{
}

OutputState::OutputState(sf::RenderWindow* window_)
    : State(), window(window_)
{
    initStuff();
}

void OutputState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
}

void OutputState::updateMousePos(const sf::Vector2i& mousePos_)
{}

void OutputState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void OutputState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
}

void OutputState::handleEvent(sf::Event& ev_)
{}

void OutputState::setExp(const std::string& exp_) {
    sopStr = exp_;
}