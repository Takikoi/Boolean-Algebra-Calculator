#pragma once

#include "State.hpp"
#include "Cell.hpp"

class ProgramState : public State
{
private:
    // DO NOT delete window in this class, because other State use it too
    sf::RenderWindow* window;

    MouseClick mouseClick;

    Cell*** cells;
    std::vector<CellType> cellType;
    unsigned short iterator = 0;
    bool cellSelected;

    void initCells();
    void initCellType();
protected:
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    ProgramState(sf::RenderWindow* window_);
    ~ProgramState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

