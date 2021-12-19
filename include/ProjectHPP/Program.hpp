#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "ProgramState.hpp"

class Program
{
private:
    sf::VideoMode vidmode;                      // window dimension
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Clock dtClock;

    float dtTime = 0.f;                         // delta time 
    void initWindow();
    void initStates();

    std::stack<State*> states;                  // cannot create objects of abstract class, but pointer instead

public:
    Program();
    ~Program();

    const bool running() const;

    void pollEvent();
    void updateDtTime();                        // update delta time
    void update();
    void render();
};

