#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "ProgramState.hpp"

class Program
{
private:
    // Core
    std::string title;
    sf::VideoMode windowBounds;                 // window dimension
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Clock dtClock;

    float dtTime = 0.f;                         // delta time
    sf::Vector2i windowPos;
    sf::Vector2i mousePos;

    std::stack<State*> states;                  // cannot create objects of abstract class, but pointer instead
    std::map<std::string,  int> supportedKeys; 

    void initWindow();
    void initStates();
    void initKeys();

public:
    Program();
    ~Program();

    const bool running() const;
    void updateWindowPos();
    const sf::Vector2i& getWindowPos() const;
    void updateMousePos();
    const sf::Vector2i& getMousePos() const;

    void pollProgramEvent();
    void updateDtTime();                        // update delta time
    void update();
    void render();
};

