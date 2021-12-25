#pragma once

#include "State.hpp"
#include "Cell.hpp"

class ProgramState : public State
{
private:
    Cell*** cells;
    std::map<short, std::string> cellType;
    
    void initCells();
protected:
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    ProgramState();
    ~ProgramState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

