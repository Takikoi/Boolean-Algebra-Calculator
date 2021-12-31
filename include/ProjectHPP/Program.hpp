#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "ProgramState.hpp"

class Program
{
private:
    // Core
    std::string title;
    int FPS = 60;
    sf::VideoMode windowBounds;                 // window dimension
    sf::VideoMode screenBounds;                 // screen resolution
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Clock dtClock;

    float dtTime = 0.f;                         // delta time
    sf::Vector2i windowPos;
    sf::Vector2i mousePos;

    ProgramState* programState;                  // cannot create objects of abstract class, but pointer instead

    void initWindow();
    void initStates();

public:
    Program();
    ~Program();

    void info() const;

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

