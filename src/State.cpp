#include "State.hpp"

State::~State()
{
    delete window;
}

State::State(sf::RenderWindow* window_)
{
    window = window_;
}