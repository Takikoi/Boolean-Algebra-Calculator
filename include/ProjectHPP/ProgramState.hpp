#pragma once

#include "State.hpp"

class ProgramState : public State
{
private:
    
public:
    ProgramState(sf::RenderWindow* window_);
    ~ProgramState();

    void updateKeyBinds(const float& dtTime_);
    void endState();

    void update(const float& dtTime_);
    void render(sf::RenderTarget* target_ = nullptr);
};

