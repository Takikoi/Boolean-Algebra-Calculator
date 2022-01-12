#include "State.hpp"

State::~State()
{
}

State::State(sf::RenderWindow* window_)
    : window(window_)
{
}

const bool& State::exitState() const {
    return exit;
}

const unsigned char& State::getExitFlag() const {
    return exitFlag;
}

void State::handleEvent(sf::Event& ev_)
{}

std::string& State::getExp() {
    return exp;
}