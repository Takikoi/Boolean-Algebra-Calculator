#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "State.hpp"
#include "Button.hpp"
#include "TextBox.hpp"

class TypeinInputState : public State
{
private:
    sf::Text userManual;
    sf::Text title;

    Textbox textBox;
    Button goBackButton;
    Button enterButton;

    void initUI();
    void initButtons();
    void initTextbox();

public:
    TypeinInputState(sf::RenderWindow* window_);
    ~TypeinInputState();

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);
};


