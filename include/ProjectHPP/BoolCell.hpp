#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class BoolCell
{
private:
    sf::RectangleShape outline;
    sf::Font font;
    sf::Text text;

public:
    BoolCell();
    BoolCell(const sf::Vector2f& pos_, const sf::Vector2f& size_, const sf::Font& font_, const std::string& str_);
    ~BoolCell();

    void render(sf::RenderTarget* target_);
};

