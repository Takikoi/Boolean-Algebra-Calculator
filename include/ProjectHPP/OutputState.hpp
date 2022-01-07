#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"
#include "State.hpp"

class OutputState : public State
{
private:
    sf::RenderWindow* window;

    sf::Texture backGroundTexture;
    sf::Sprite backGround;
    sf::Font font;

    std::string simplifiedExpStr;
    sf::Text simplifiedExpTxt;

    std::string sopStr;
    sf::Text sopTxt;

    void initStuff();
    
protected:
    
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    OutputState();
    OutputState(sf::RenderWindow* window_);
    ~OutputState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);
    void setExp(const std::string& exp_);
};

