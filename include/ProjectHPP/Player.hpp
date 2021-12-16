#pragma once

#include "Package.hpp"

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture textureSheet;
    sf::IntRect currentFrame;
    
    float speed = 5.f;

    void initSprite();
    void initTexture();
public:
    Player();
    ~Player();

    
    void updateMovement();
    void update();
    void render(sf::RenderTarget& target);
};

