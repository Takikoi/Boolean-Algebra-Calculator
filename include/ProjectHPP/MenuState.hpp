#pragma once

#include "State.hpp"
#include "Button.hpp"

class MenuState : public State
{
private:
    sf::Text title;
    
    Button typeInOption;
    Button graphicInputOption;

    void initButtons();
    void initUI();

public:
    MenuState(sf::RenderWindow* window_);
    ~MenuState();

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

