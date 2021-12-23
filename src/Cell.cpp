#include "Cell.hpp"

void Cell::initVariables()
{
    rec.setSize(sf::Vector2f((float)WINDOW_WIDTH / NUM_CELLS, (float)WINDOW_WIDTH / NUM_CELLS));
    rec.setFillColor(sf::Color::Cyan);
}

Cell::~Cell()
{
}

Cell::Cell(const sf::Vector2f& pos_)
{
    initVariables();
    rec.setPosition(pos_);
}


void Cell::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void Cell::render(sf::RenderTarget* target_)
{
    target_->draw(rec);
}



void Cell::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void Cell::updateMousePos(const sf::Vector2i& mousePos_)
{
}

    