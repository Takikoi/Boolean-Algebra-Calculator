#include "State.hpp"

State::~State()
{
}

State::State()
{
}

void State::checkForQuit()
{    
}

const bool& State::getQuit() const {
    return quit;
}

void State::updateMousePos()
{
}

const unsigned char& State::getExitFlag() const {
    return exitFlag;
}