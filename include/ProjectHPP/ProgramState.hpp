#pragma once

#include "State.hpp"
#include "Cell.hpp"

class ProgramState : public State
{
private:
    // DO NOT delete window in this class, because other State use it too
    sf::RenderWindow* window;
    std::map<unsigned char, std::string> expressionElement;
    std::string boolExpression;

    Cell*** cells;
    std::vector<CellType> cellType;
    unsigned short iterator = 0;
    bool cellSelected;

    void initCells();
    void initCellType();
    void initExpElement();
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

    std::string generateExpression();
    std::string exp(short x_, short y_, short flag);
    std::string exp2(short x_, short y_, unsigned char, bool up = 1);
};

