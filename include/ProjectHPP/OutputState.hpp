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
    sf::Text simplifiedExpTxt;
    sf::Text rawExpTxt;
    sf::Text sopTxt;
    short expTxt_maxperline = 35;

    std::vector<sf::Text> inputTxt;

    // Thinh's Code
    Expression rawExp;
    
    TruthTable truthTB; // truthTb must be init after expression

    // Long's code
    Tabulation simplifiedExp;

    Button reStartButton;
    
    void initUI();
    void initBoolResult();
    void initButtons();
public:
    OutputState(sf::RenderWindow* window_, const std::string& exp_);
    ~OutputState();

    void update(const float& dtTime_, const sf::Vector2i& mousePos_);
    void render(sf::RenderTarget* target_ = NULL);
};

