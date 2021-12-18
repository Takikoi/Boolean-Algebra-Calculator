#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class State
{
protected:
    sf::RenderWindow* window;
    std::vector<sf::Texture> textures;  // it's an array.....so plural

public:
    State(sf::RenderWindow* window_);
    virtual ~State();

    virtual void endState() = 0;
    virtual void update(const float& dtTime_) = 0;
    virtual void render(sf::RenderTarget* target_) = 0;

    /* These are "pure virtual fuction" declaration
    * having them = 0 to specify them as a pure virtual functions
    * Pure virtual functions dont need to be defined like normal functions in a class, 
    * they are meant to be polymorphed in the inheritants
    */
};

