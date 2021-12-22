#include "State.hpp"

State::~State()
{
    delete window;
}

State::State(sf::RenderWindow* window_)
{
    window = window_;
}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        //quit = true;
    }
    
}

const bool& State::getQuit() const {
    return quit;
}

void State::updateMousePos()
{
    
}

