#include "Cell.hpp"

void Cell::initVariables()
{
    rec.setSize(sf::Vector2f((float)WINDOW_WIDTH / NUM_CELLS, (float)WINDOW_WIDTH / NUM_CELLS));
    rec.setFillColor(sf::Color::Cyan);
}

void Cell::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/texture.png"))
        std::cout << "[ERROR] : Failed to load texture.";
    else 
        std::cout << "[MESSAGE]: Successfully loaded texture sheet.\n";
}

void Cell::initSprites()
{
    sprites.setTexture(textureSheet);
    //sprites.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

Cell::~Cell()
{
}

Cell::Cell() {}

Cell::Cell(const sf::Vector2f& pos_)
{
    initVariables();
    initTexture();
    //textureSheet = *tex_;
    initSprites();
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

void Cell::setColor(sf::Color color_)
{
    rec.setFillColor(color_);
}