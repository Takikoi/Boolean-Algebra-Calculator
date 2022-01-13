#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class Cell
{
private:
    sf::RectangleShape boundingBox;

    sf::Texture textureSheet;
    sf::Sprite sprites;
    std::map<unsigned char, sf::IntRect> texRec;
    unsigned char currentType = EMPTY_CELL;

    void initBounds();
    void initTexture();

public:
    Cell();
    Cell(const sf::Vector2f& pos_);
    ~Cell();

    void update(const float& dtTime_, const sf::Vector2i& mousePos_, const CellType& type_);
    void render(sf::RenderTarget* target_ = NULL);

    bool cursorDetected(const sf::Vector2i& mousePos_);
    void changeToNextType();
    void changeToPreviousType();
    const unsigned char& getCurrentType() const;
};

