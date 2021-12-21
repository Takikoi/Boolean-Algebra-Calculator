#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "Entity.hpp" 

class State
{
protected:
    sf::RenderWindow* window;
    std::vector<sf::Texture> backgrounds;
    sf::Vector2i mousePos;

    bool quit;

public:
    State(sf::RenderWindow* window_);
    virtual ~State();

    void checkForQuit();
    void updateMousePos();
    const bool& getQuit() const;

    virtual void endState() = 0;
    virtual void updateInput(const float& dtTime_) = 0;
    virtual void update(const float& dtTime_) = 0;
    virtual void render(sf::RenderTarget* target_ = NULL) = 0;

    /* These are "pure virtual fuction" declaration
    * having them = 0 to specify them as a pure virtual functions
    * Pure virtual functions dont need to be defined like normal functions in a class, 
    * they are meant to be polymorphed in the inheritants
    */
};