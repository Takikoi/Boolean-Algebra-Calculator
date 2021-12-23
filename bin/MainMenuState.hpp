#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "State.hpp"

class MainMenuState : public State
{
private:
    
public:
    MainMenuState(/* args */);
    ~MainMenuState();

    void updateInput(const float& dtTime_);
    void endState();

    void update(const float& dtTime_);
    void render(sf::RenderTarget* target_ = nullptr);
};

