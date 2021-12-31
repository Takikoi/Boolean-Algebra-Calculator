#include "BoolExpression.hpp"

BoolExpression::~BoolExpression()
{
    // do not delete cells here
}

BoolExpression::BoolExpression()
{
}

BoolExpression::BoolExpression(Cell*** cells_)
    : valid(false)
{
    cells = cells_;
}

std::string BoolExpression::getExpression() 
{
    sf::Vector2i outputPos = getOutputCellPosition();
    // std::cout << "pos: " << outputPos.x << ", " << outputPos.y << "\n";
    check_ValidNeighboringCells();
    std::cout << "Valid? : " << valid << "\n";
    return generateExpression(outputPos.x, outputPos.y - 1);
}

sf::Vector2i BoolExpression::getOutputCellPosition()
{
    sf::Vector2i pos(0, 0);
    for (pos.y = NUM_CELLS - 1; pos.y >= 0; --pos.y)
        for (pos.x = 0; pos.x < NUM_CELLS; ++pos.x)
            if (cells[pos.x][pos.y]->getCurrentType() == SIGNAL_OUT_1)
            {
                return pos;
            }
    std::cout << "Output cell not found\n";
    return sf::Vector2i(-1, 0);
}

void BoolExpression::check_CellContinuity()
{}

void BoolExpression::check_ValidNeighboringCells()
{
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->getCurrentType() != EMPTY_CELL)
            {    
                std::cout << i << ", " << j << "\n";
                std::cout << "CellType: " << (short)cells[i][j]->getCurrentType() << "\n";

                valid = false;
                switch (cells[i][j]->getCurrentType())
                {
                case OR_GATE:
                case AND_GATE:
                    if ((cells[i][j + 1]->getCurrentType() == SIGNAL_OUT_1 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_VERTICAL 
                    ||   cells[i][j + 1]->getCurrentType() == NOT_GATE 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_RIGHT) 

                    &&  
                        (cells[i][j - 1]->getCurrentType() == GATE_INPUT))
                        valid = true;
                    break;
                
                case NOT_GATE:
                case WIRE_VERTICAL:
                    if ((cells[i][j + 1]->getCurrentType() == SIGNAL_OUT_1 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_VERTICAL 
                    ||   cells[i][j + 1]->getCurrentType() == NOT_GATE 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_RIGHT)

                    &&  
                        (cells[i][j - 1]->getCurrentType() == SIGNAL_IN_A 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_B
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_C
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_D
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_E
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_F 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_G
                    ||   cells[i][j - 1]->getCurrentType() == OR_GATE
                    ||   cells[i][j - 1]->getCurrentType() == AND_GATE
                    ||   cells[i][j - 1]->getCurrentType() == NOT_GATE
                    ||   cells[i][j - 1]->getCurrentType() == WIRE_VERTICAL ))
                        valid = true;
                    break;

                case WIRE_HORIZONTAL:
                    if ((cells[i - 1][j]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i - 1][j]->getCurrentType() == WIRE_HORIZONTAL
                    ||   cells[i - 1][j]->getCurrentType() == GATE_INPUT)
                    
                    &&
                        (cells[i + 1][j]->getCurrentType() == WIRE_CORNER_RIGHT
                    ||   cells[i + 1][j]->getCurrentType() == WIRE_HORIZONTAL
                    ||   cells[i - 1][j]->getCurrentType() == GATE_INPUT))
                        valid = true;
                    break;    
                
                case GATE_INPUT:
                    if ((cells[i][j + 1]->getCurrentType() == OR_GATE
                    ||   cells[i][j + 1]->getCurrentType() == AND_GATE)
                    
                    &&
                        (cells[i - 1][j]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i - 1][j]->getCurrentType() == WIRE_HORIZONTAL)
                    
                    &&
                        (cells[i + 1][j]->getCurrentType() == WIRE_CORNER_RIGHT
                    ||   cells[i + 1][j]->getCurrentType() == WIRE_HORIZONTAL))
                        valid = true;
                    break;

                case WIRE_CORNER_LEFT:
                    if ((cells[i][j - 1]->getCurrentType() == SIGNAL_IN_A 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_B
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_C
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_D
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_E
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_F 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_G
                    ||   cells[i][j - 1]->getCurrentType() == OR_GATE
                    ||   cells[i][j - 1]->getCurrentType() == AND_GATE
                    ||   cells[i][j - 1]->getCurrentType() == NOT_GATE
                    ||   cells[i][j - 1]->getCurrentType() == WIRE_VERTICAL)
                    
                    &&
                        (cells[i + 1][j]->getCurrentType() == WIRE_CORNER_RIGHT
                    ||   cells[i + 1][j]->getCurrentType() == WIRE_HORIZONTAL
                    ||   cells[i + 1][j]->getCurrentType() == GATE_INPUT))
                        valid = true;
                    break;

                case WIRE_CORNER_RIGHT:
                    if ((cells[i][j - 1]->getCurrentType() == SIGNAL_IN_A 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_B
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_C
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_D
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_E
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_F 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_G
                    ||   cells[i][j - 1]->getCurrentType() == OR_GATE
                    ||   cells[i][j - 1]->getCurrentType() == AND_GATE
                    ||   cells[i][j - 1]->getCurrentType() == NOT_GATE
                    ||   cells[i][j - 1]->getCurrentType() == WIRE_VERTICAL)
                    
                    &&
                        (cells[i - 1][j]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i - 1][j]->getCurrentType() == WIRE_HORIZONTAL
                    ||   cells[i - 1][j]->getCurrentType() == GATE_INPUT))
                        valid = true;
                    break;
                    
                case SIGNAL_IN_A:
                case SIGNAL_IN_B:
                case SIGNAL_IN_C:
                case SIGNAL_IN_D:
                case SIGNAL_IN_E:
                case SIGNAL_IN_F:
                case SIGNAL_IN_G:
                    if ((cells[i][j + 1]->getCurrentType() == SIGNAL_OUT_1 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_VERTICAL 
                    ||   cells[i][j + 1]->getCurrentType() == NOT_GATE 
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_LEFT
                    ||   cells[i][j + 1]->getCurrentType() == WIRE_CORNER_RIGHT))
                        valid = true;
                    break;
                
                case SIGNAL_OUT_1:
                    if  (cells[i][j - 1]->getCurrentType() == SIGNAL_IN_A 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_B
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_C
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_D
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_E
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_F 
                    ||   cells[i][j - 1]->getCurrentType() == SIGNAL_IN_G
                    ||   cells[i][j - 1]->getCurrentType() == OR_GATE
                    ||   cells[i][j - 1]->getCurrentType() == AND_GATE
                    ||   cells[i][j - 1]->getCurrentType() == NOT_GATE
                    ||   cells[i][j - 1]->getCurrentType() == WIRE_VERTICAL)
                        valid = true;
                    break;
                }
                if (!valid) goto exit_loop;
            }   
        }
    }
    exit_loop:;
}

std::string BoolExpression::generateExpression(short x_, short y_, bool checkUpward_)
{
    std::string result = "";
    if (x_ != -1 && y_ != -1)
    {
        if (valid)
        {    
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

            case EMPTY_CELL:
                valid = false;
                break;
            }
            return result;
        }
        else std::cout << "Invalid circuit\n";
    }
    return "";
}