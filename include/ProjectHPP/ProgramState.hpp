#pragma once

#include "State.hpp"
#include "Cell.hpp"
#include "BoolExpression.hpp"

class ProgramState : public State
{
private:
    // DO NOT delete window in this class, because other State use it too
    sf::RenderWindow* window;
    std::map<unsigned char, std::string> expressionElement;
    std::string boolExpression;
    

    Cell*** cells;
    Cell testCell;
    std::vector<CellType> cellType;
    unsigned short iterator = 0;
    bool cellSelected;

    BoolExpression expression;

    sf::Texture UI_barTexture;
    sf::Sprite UI_bar;

    sf::Texture backButtonTexture;
    sf::Sprite backButton;

    void initCells();
    void initCellType();
    void initExpElement();
    void initTexture();
    
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

