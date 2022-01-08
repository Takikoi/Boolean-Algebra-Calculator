#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "State.hpp"
#include "Button.hpp"
#include "TextBox.hpp"

class TypeinInputState : public State
{
private:
    sf::RenderWindow* window;
    sf::Font font;

    sf::Texture backGroundTexture;
    sf::Sprite backGround;

    sf::Text userManual;
    sf::Text title;

    Textbox textBox;
    void initStuff();

public:
    TypeinInputState(sf::RenderWindow* window_);
    ~TypeinInputState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);
};


