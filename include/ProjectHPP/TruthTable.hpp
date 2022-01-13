#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"
#include "BoolCell.hpp"

class TruthTable
{
private:
    sf::Vector2f posTBVal; // default posTBVal
    sf::Vector2f posTBOrigin;
    sf::Vector2f boolCellSize;
    bool** truthTBValue;
    bool* truthTBOuput;

    std::string exp;
    unsigned short numCol;
    unsigned short numRow;
    
    std::vector<BoolCell> inputSignalText;
    BoolCell** boolValCells;
    BoolCell* boolOutputCells;

    unsigned int charSize = 24;
    sf::Font font;

    int gap = 15; // gap between 2 tables
    
    void initVariables();
    void initBoolCell();

public:
    TruthTable(const std::string& str_, bool** entry_ = nullptr, bool* output_ = nullptr);
    ~TruthTable();

    void render(sf::RenderTarget* target_);
};

