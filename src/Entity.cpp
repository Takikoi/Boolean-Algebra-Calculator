#include "Entity.hpp"

Entity::~Entity()
{
}

Entity::Entity()
{
    rec.setSize(sf::Vector2f(50.f, 50.f));
    rec.setFillColor(sf::Color::Green);
}

// ######################################################################## (Main Update & Render)

void Entity::update(const float& dtTime_)
{
    
}

void Entity::render(sf::RenderTarget* target_)
{
    target_->draw(rec);
}

// ######################################################################## (Program functions)

void Entity::move(const float dtTime_, const sf::Vector2f dir_)
{
    rec.move(dir_.x * movementSpeed * dtTime_, dir_.y * movementSpeed * dtTime_);
}