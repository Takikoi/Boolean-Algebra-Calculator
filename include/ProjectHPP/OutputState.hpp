#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"
#include "State.hpp"
#include "TruthTable.hpp"
#include "Button.hpp"

// Thinh's
#include "TruthTableBool.h"
#include "Expression.h"

// Long's
#include "Tabulation.h"


class OutputState : public State
{
private:
    sf::RenderWindow* window;

    sf::Texture backGroundTexture;
    sf::Sprite backGround;
    sf::Font font;

    std::string simplifiedExpStr;
    sf::Text simplifiedExpTxt;

    std::string sopStr;
    sf::Text sopTxt;
    short sopTxt_maxperline = 35;

    std::vector<sf::Text> inputGates;

    // Thinh's Code
    Expression rawExp;
    TruthTable truthTB; // truthTb must be init after expression

    // Long's code
    Tabulation simplifiedExp;

    Button reStartButton;
    
    void initStuff();
    
protected:
    
    // std::vector<sf::Texture> textures;
    // sf::Vector2i mousePos;
    // bool quit;

public:
    OutputState();
    OutputState(sf::RenderWindow* window_, const std::string& exp_);
    ~OutputState();

    void updateInput(const float& dtTime_, const sf::Vector2i& mousePos_);
    void updateMousePos(const sf::Vector2i& mousePos_);

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);

    void handleEvent(sf::Event& ev_);
    void setExp(const std::string& exp_);
};

