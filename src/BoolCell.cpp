#include "BoolCell.hpp"



BoolCell::~BoolCell()
{
}

BoolCell::BoolCell()
{
}

BoolCell::BoolCell(const sf::Vector2f& pos_, const sf::Vector2f& size_, const sf::Font& font_, const std::string& str_)
{
    outline.setSize(size_);
    outline.setPosition(pos_);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color(78, 78, 78));
    outline.setOutlineThickness(5);

    text.setFont(font_);
    text.setColor(sf::Color(78, 78, 78));
    text.setString(str_);

    text.setPosition({pos_.x + size_.x/3, pos_.y + size_.y/4});
}



void BoolCell::render(sf::RenderTarget* target_)
{
    target_->draw(outline);
    target_->draw(text);
}