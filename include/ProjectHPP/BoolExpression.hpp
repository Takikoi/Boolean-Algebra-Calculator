#pragma once

#include "SYSTEM_modules.hpp"
#include "SFML_modules.hpp"

#include "Cell.hpp"

class BoolExpression
{
private:
    std::string exp;
    Cell*** cells;
    bool valid;

public:
    BoolExpression();
    BoolExpression(Cell*** cells_);
    ~BoolExpression();

    
    std::string getExpression();

    sf::Vector2i getOutputCellPosition();
    void check_CellContinuity();
    void check_ValidNeighboringCells();
    std::string generateExpression(short x_, short y_, bool checkUpward_ = true);
};

