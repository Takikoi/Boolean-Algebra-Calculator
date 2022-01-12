#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class State
{
protected:
    sf::RenderWindow* window;
    unsigned char exitFlag;             // to determine what happens after exiting state
    bool exit = false;                  // exit current state or not
    std::string exp = "";

    sf::Texture backGroundTexture;
    sf::Sprite backGround;
    sf::Font font;

public:
    State(sf::RenderWindow* window_);
    virtual ~State();

    const bool& exitState() const;              // return exit boolean
    virtual std::string& getExp();              // return the expression received in that state
    const unsigned char& getExitFlag() const;   // return exit flag

    virtual void handleEvent(sf::Event& ev_);   // process user interaction
    
    virtual void update(const float& dtTime_, const sf::Vector2i& mousePos_) = 0; 
    virtual void render(sf::RenderTarget* target_ = NULL) = 0;
};