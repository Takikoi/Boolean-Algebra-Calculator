#include "Game.hpp"

Game::Game()
{
    // Init window 
    videoMode = sf::VideoMode(800, 600);
    window.create(videoMode, "Project 0", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(144);
    // Create Player
    initPlayer();
}

Game::~Game() {
    delete player;
}

const bool Game::running() const {
    return window.isOpen();
}

void Game::pollEvents()
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window.close();
            break;
        }
    }
    
}

void Game::update()
{
    pollEvents();
    updatePlayer();
}

void Game::render()
{
    window.clear(sf::Color::Transparent);

    this->renderPlayer();

    window.display();
}

void Game::initPlayer()
{
    player = new Player;
}

void Game::updatePlayer()
{
    player->update(); 
}

void Game::renderPlayer()
{
    player->render(window);
}