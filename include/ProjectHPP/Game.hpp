#pragma once

#include "Package.hpp"
#include "Player.hpp"

class Game
{
private:
    // Window
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Objects
    Player* player;
    void initPlayer();
    
public:
    Game();
    virtual ~Game();
    
    const bool running() const;


    void pollEvents();

    void updatePlayer();
    void renderPlayer();

    void update();
    void render();
};

