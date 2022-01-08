#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"


class State
{
protected:
    sf::Vector2i mousePos;
    unsigned char exitFlag;
    bool quit;

public:
    State();
    virtual ~State();

    void checkForQuit();
    virtual void updateMousePos();
    const bool& getQuit() const;
    const unsigned char& getExitFlag() const;
    virtual void handleEvent(sf::Event& ev_);

    virtual void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_) = 0;
    virtual void update(const float& dtTime_, const sf::Vector2i& mousePos_) = 0;
    virtual void render(sf::RenderTarget* target_ = NULL) = 0;

    /* These are "pure virtual fuction" declaration
    * having them = 0 to specify them as a pure virtual functions
    * Pure virtual functions dont need to be defined like normal functions in a class, 
    * they are meant to be polymorphed in the inheritants
    */
};