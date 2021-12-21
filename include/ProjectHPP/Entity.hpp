#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class Entity
{
protected:
    sf::RectangleShape boundBox;
    sf::Sprite sprite;
    sf::Vector2i mousePos;
    
public:
    Entity();
    ~Entity();

    virtual void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    bool checkMouseCollision();
    virtual void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    virtual void render(sf::RenderTarget* target_ = NULL);

    virtual void move(const float dtTime_, const sf::Vector2f dir);
};

