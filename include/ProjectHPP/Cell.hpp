#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class Cell
{
private:
    sf::RectangleShape rec;
    sf::Texture textureSheet;
    sf::Sprite sprites;
    std::map<CellType, sf::IntRect> texRec;

    void initVariables();
    void initTexture();
    void initSprites();
public:
    Cell();
    Cell(const sf::Vector2f& pos_);
    ~Cell();
    
    void setColor(const sf::Color& color_);

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_, const CellType& type_);
    void render(sf::RenderTarget* target_ = NULL);

    bool cursorDetected(const sf::Vector2i& mousePos_);
};

