#pragma once

#include "State.hpp"
#include "Cell.hpp"
#include "BoolExpression.hpp"
#include "Button.hpp"

class GraphicInputState : public State
{
private:
    // Cells field
    Cell*** cells;

    BoolExpression expression;

    // UIs
    sf::Texture UI_barTexture;
    sf::Sprite UI_bar;
    sf::Text UI_log;
    sf::Text userManual;
    sf::Font font;

    Button goBackButton;
    Button enterButton;

    // Inits
    void initCells();
    void initUI();
    void initText();

public:
    GraphicInputState(sf::RenderWindow* window_);
    ~GraphicInputState();

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

