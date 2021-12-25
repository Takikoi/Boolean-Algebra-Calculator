#include "Cell.hpp"

void Cell::initVariables()
{
    rec.setSize(sf::Vector2f((float)WINDOW_WIDTH / NUM_CELLS, (float)WINDOW_WIDTH / NUM_CELLS));
    rec.setFillColor(sf::Color::Cyan);
}

void Cell::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/Boolean Assets.png"))
        std::cout << "[ERROR] : Failed to load texture.";
}

void Cell::initSprites()
{
    logicComponents.emplace("OR gate", sf::Sprite(textureSheet, sf::IntRect(0, 0, 64, 64)));
    logicComponents.emplace("AND gate", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE, 0, 64, 64)));
    logicComponents.emplace("NOT gate", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE*2, 0, 64, 64)));
    logicComponents.emplace("Gate input junction", sf::Sprite(textureSheet, sf::IntRect(0, CELL_SIZE, 64, 64)));
    logicComponents.emplace("Gate left input", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE, CELL_SIZE, 64, 64)));
    logicComponents.emplace("Gate right input", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE*2, CELL_SIZE, 64, 64)));
    logicComponents.emplace("Signal A", sf::Sprite(textureSheet, sf::IntRect(0, CELL_SIZE*2, 64, 64)));
    logicComponents.emplace("Signal B", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE, CELL_SIZE*2, 64, 64)));
    logicComponents.emplace("Signal C", sf::Sprite(textureSheet, sf::IntRect(CELL_SIZE*2, CELL_SIZE*2, 64, 64)));
}

Cell::~Cell()
{
}

Cell::Cell() {}

Cell::Cell(const sf::Vector2f& pos_)
{
    initVariables();
    initTexture();
    initSprites();
    sprites = logicComponents["Signal A"];
    sprites.setPosition(pos_);
    rec.setPosition(pos_);
}


void Cell::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void Cell::render(sf::RenderTarget* target_)
{
    //target_->draw(rec);
    target_->draw(sprites);
}



void Cell::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void Cell::updateMousePos(const sf::Vector2i& mousePos_)
{}

void Cell::setColor(const sf::Color& color_)
{
    rec.setFillColor(color_);
}