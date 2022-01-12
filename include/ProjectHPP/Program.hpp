#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "MenuState.hpp"
#include "TypeinInputState.hpp"
#include "GraphicInputState.hpp"
#include "OutputState.hpp"

class Program
{
private:
    // Core
    std::string title;
    int FPS = 60;
    sf::VideoMode windowBounds;                 // window dimension
    sf::VideoMode screenBounds;                 // monitor resolution
    sf::RenderWindow* window;                   // the actual window displayed on the screen
    sf::Event ev;                               // the interaction from user 
    sf::Clock dtClock;                          // the clock of the program
    float dtTime = 0.f;                         // the time taken to complete 1 loop of update and render      
    sf::Vector2i windowPos;
    sf::Vector2i mousePos;
    
    // Objects : Program States
    std::map<unsigned char, State*> states;     // the main structure of the program
    unsigned char key = MENU_STATE;            // initialize the 1st state to display to the window

    // Initialisation functions
    void initWindow();
    void initStates();

    // Update function for Core
    void updateWindowPos();
    void updateMousePos();
    void pollProgramEvent();                    // check user interaction
    void updateDtTime();                        // update delta time

public:
    Program();
    ~Program();

    void info() const;                          // show program info in terminal
    const bool running() const;                 // whether the program is running or not
    
    void update();                              // update objects
    void render();                              // render and display objects to window
};