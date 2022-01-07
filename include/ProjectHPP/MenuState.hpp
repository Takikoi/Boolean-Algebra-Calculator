#pragma once

#include "State.hpp"
#include "Button.hpp"

class MenuState : public State
{
private:
    sf::RenderWindow* window;
    sf::Text title;
    sf::Font font;
    
    Button typeInOption;
    Button graphicInputOption;
    sf::Texture backGroundTexture;
    sf::Sprite backGround;

    

    void initButtons();
    void initTexture();
protected:
    
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    MenuState();
    MenuState(sf::RenderWindow* window_);
    ~MenuState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);

    
};

