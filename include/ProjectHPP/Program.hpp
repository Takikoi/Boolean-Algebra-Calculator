#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "State.hpp"
#include "ProgramState.hpp"

class Program
{
private:
    sf::VideoMode vidmode;                      // window dimension
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Clock dtClock;

    float dtTime;                               // delta time 
    void initVariables();
    void initStates();

    std::stack<State*> states;                  // cannot create objects of abstract class

public:
    Program();
    ~Program();

    const bool running() const;

    void pollEvent();
    void updateDtTime();                        // update delta time
    void update();
    void render();
};

