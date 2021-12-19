#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

class Entity
{
private:
protected:
    sf::RectangleShape rec;
    const float movementSpeed = 100;;
public:
    Entity();
    ~Entity();

    virtual void move(const float dtTime_, const sf::Vector2f dir);
    virtual void update(const float& dtTime_);
    virtual void render(sf::RenderTarget* target_ = nullptr);
};

