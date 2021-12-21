#pragma once

#include "State.hpp"

class ProgramState : public State
{
private:
    Entity logicGate;

protected:
    // sf::RenderWindow* window;
    // std::vector<sf::Texture> textures;
    // bool quit;

public:
    // State(sf::RenderWindow* window_);
    ProgramState(sf::RenderWindow* window_);
    ~ProgramState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

