#include "Entity.hpp"

Entity::~Entity()
{
}

Entity::Entity()
{
    boundBox.setPosition(100, 100);
    boundBox.setSize(sf::Vector2f(150.f, 150.f));
    boundBox.setFillColor(sf::Color::Green);
}

// ######################################################################## (Main Update & Render)

void Entity::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    updateInput(dtTime_, mousePos_);
}

void Entity::render(sf::RenderTarget* target_)
{
    target_->draw(boundBox);
}

// ######################################################################## (Program functions)

void Entity::move(const float dtTime_, const sf::Vector2f dir_)
{
    
}

void Entity::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    mousePos = mousePos_;
    std::cout << checkMouseCollision() << std::endl;

}

bool Entity::checkMouseCollision()
{
    if ((float)mousePos.x >= boundBox.getPosition().x && (float)mousePos.x <= (boundBox.getPosition().x + boundBox.getSize().x)
     && (float)mousePos.y >= boundBox.getPosition().y && (float)mousePos.y <= (boundBox.getPosition().y + boundBox.getSize().y))
    {
        return true;
    }
    else return false;
}