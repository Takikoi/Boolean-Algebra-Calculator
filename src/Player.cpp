#include "Player.hpp"

void Player::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/Walk.png"))
        std::cout << "[ERROR]: Could not load texture sheet.\n";
    else 
        std::cout << "[MESSAGE]: Successfully loaded texture sheet.\n";
}

void Player::initSprite()
{
    sprite.setTexture(textureSheet);
    currentFrame = sf::IntRect(0, 0, 60, 60);
    sprite.setTextureRect(currentFrame);
}

Player::Player()
{
    initTexture();
    initSprite();
}

Player::~Player()
{
}

void Player::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sprite.move(-speed, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sprite.move(speed, 0.f);
    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        sprite.move(0.f, -speed);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        sprite.move(0.f, speed);
}

void Player::update()
{
    updateMovement();
}

void Player::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}