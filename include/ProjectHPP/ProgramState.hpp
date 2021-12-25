#pragma once

#include "State.hpp"
#include "Cell.hpp"

class ProgramState : public State
{
private:
    Cell*** cells;
    Cell* foo;
    sf::Texture textureSheet;
    sf::Sprite sprites;

    void initCells();
protected:
    // std::vector<sf::Texture> textures;
    // bool quit;

public:
    ProgramState();
    ~ProgramState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

