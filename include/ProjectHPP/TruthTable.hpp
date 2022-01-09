#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"
#include "BoolCell.hpp"

class TruthTable
{
private:
    sf::Vector2f pos; // default pos
    sf::Vector2f boolCellSize;
    bool** truthTBValue;

    std::string exp;
    unsigned short numCol;
    unsigned short numRow;
    
    std::vector<sf::Text> inputSignalText;
    BoolCell** boolCells;
    BoolCell* testCell;

    unsigned int charSize = 24;

    sf::Font font;
public:
    void initStuff();

    TruthTable();
    TruthTable(const std::string& str_, bool** entry_ = nullptr);
    ~TruthTable();

    void generateTruthTB();
    void render(sf::RenderTarget* target_);

    void setExp(int a);
    void setTBVal(bool** entry_);
};

