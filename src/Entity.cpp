#include "Entity.hpp"

Entity::~Entity()
{
}

Entity::Entity(/* args */)
{
    rec.setSize(sf::Vector2f(50.f, 50.f));
    rec.setFillColor(sf::Color::Green);
}

void Entity::update(const float& dtTime_)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(dtTime_, sf::Vector2f(-1.f, 0.f));
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(dtTime_, sf::Vector2f(1.f, 0.f));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(dtTime_, sf::Vector2f(0.f, -1.f));
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(dtTime_, sf::Vector2f(0.f, 1.f));
}

void Entity::render(sf::RenderTarget* target_)
{
    target_->draw(rec);
}

void Entity::move(const float dtTime_, const sf::Vector2f dir_)
{
    rec.move(dir_.x * movementSpeed * dtTime_, dir_.y * movementSpeed * dtTime_);
}