#pragma once

#include "State.hpp"
#include "Cell.hpp"
#include "BoolExpression.hpp"

class GraphicInputState : public State
{
private:
    // DO NOT delete window in this class, because other State use it too
    sf::RenderWindow* window;

    Cell*** cells;
    Cell testCell;

    BoolExpression expression;

    sf::Texture UI_barTexture;
    sf::Sprite UI_bar;

    sf::Texture backButtonTexture;
    sf::Sprite backButton;

    sf::Text UI_log;
    sf::Font font;

    void initCells();
    void initTexture();
    void initText();
    
protected:
    
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    GraphicInputState(sf::RenderWindow* window_);
    ~GraphicInputState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);
};

