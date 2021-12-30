#include "BoolExpression.hpp"

BoolExpression::~BoolExpression()
{
    // do not delete cells here
}

BoolExpression::BoolExpression()
{
}

BoolExpression::BoolExpression(Cell*** cells_)
    : valid(true)
{
    cells = cells_;
}

std::string BoolExpression::getExpression() 
{
    check_CellContinuity();
    check_ValidNeighboringCells();
    //exp = generateExpression(getOutputCellLocation().x, getOutputCellLocation().y);
    
    return generateExpression(getOutputCellLocation().x, getOutputCellLocation().y - 1);
}

sf::Vector2i BoolExpression::getOutputCellLocation()
{
    sf::Vector2i pos;
    for (pos.y = NUM_CELLS - 1; pos.y >= 0; --pos.y)
        for (pos.x = 0; pos.x < NUM_CELLS; ++pos.x)
            if (cells[pos.x][pos.y]->getCurrentType() == SIGNAL_OUT_1)
            {
                goto endLoop;
            }
                
    endLoop:
    return pos;
}

void BoolExpression::check_CellContinuity()
{}

void BoolExpression::check_ValidNeighboringCells()
{}

std::string BoolExpression::generateExpression(short x_, short y_, bool checkUpward_)
{
    std::string result = "";
    switch (cells[x_][y_]->getCurrentType())
    {
// LOGIC GATES
    case OR_GATE:
        result = "( + )";
        result.replace(1, 1, generateExpression(x_, y_ - 1, true));
        result.replace(result.size() - 2, 1, generateExpression(x_, y_ - 1, false));
        break;
    
    case AND_GATE:
        result = " * ";
        result.replace(0, 1, generateExpression(x_, y_ - 1, true));
        result.replace(result.size() - 1, 1, generateExpression(x_, y_ - 1, false));
        break;

    case NOT_GATE:
        result = "( )'";
        result.replace(1, 1, generateExpression(x_, y_ - 1));
        break;

// CONNECTION WIRE
    case GATE_INPUT:
    case WIRE_HORIZONTAL:
        result = (checkUpward_ ? generateExpression(x_ - 1, y_, true) : generateExpression(x_ + 1, y_, false));
        break;

    case WIRE_CORNER_LEFT:
    case WIRE_CORNER_RIGHT:
    case WIRE_VERTICAL:
        result = generateExpression(x_, y_ - 1);
        break;

    case SIGNAL_IN_A:
        result = "A";
        break;
    
    case SIGNAL_IN_B:
        result = "B";
        break;
    
    case SIGNAL_IN_C:
        result = "C";
        break;

    case SIGNAL_IN_D:
        result = "D";
        break;
    
    case SIGNAL_IN_E:
        result = "E";
        break;
    
    case SIGNAL_IN_F:
        result = "F";
        break;

    case SIGNAL_IN_G:
        result = "G";
        break;
    }
    return result;
}