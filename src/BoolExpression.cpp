#include "BoolExpression.hpp"

BoolExpression::~BoolExpression()
{
    // do not delete cells here
    std::cout << "BoolExp deleted\n";
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
    return generateExpression(outputPos.x - 1, outputPos.y);
}

sf::Vector2i BoolExpression::getOutputCellPosition()
{
    sf::Vector2i pos(0, 0);
    for (pos.x = CELL_FIELD_DIM_X - 1; pos.x >= 0; --pos.x)
        for (pos.y = 0; pos.y < CELL_FIELD_DIM_Y; ++pos.y)
            if (cells[pos.x][pos.y]->getCurrentType() == SIGNAL_OUT_1)
            {
                return pos;
            }
    std::cout << "Output cell not found\n";
    return sf::Vector2i(-1, 0);
}

void BoolExpression::check_ValidNeighboringCells()
{
    for (short i = 0; i < CELL_FIELD_DIM_X; ++i)
    {
        for (short j = 0; j < CELL_FIELD_DIM_Y; ++j)
        {
            if (cells[i][j]->getCurrentType() != EMPTY_CELL)
            {    
                std::cout << i << ", " << j << "\n";

                valid = false;
                
                unsigned char right(0), left(0), top(0), bottom(0);
                if (i != (CELL_FIELD_DIM_X - 1))
                    right = cells[i + 1][j]->getCurrentType();

                if (i != 0)
                    left = cells[i - 1][j]->getCurrentType();

                if (j != 0)
                    top = cells[i][j - 1]->getCurrentType();

                if (j != (CELL_FIELD_DIM_Y - 1))
                    bottom = cells[i][j + 1]->getCurrentType();

                switch (cells[i][j]->getCurrentType())
                {
                case OR_GATE:
                case AND_GATE:
                    if (i != 0 || j != 0 || i != (CELL_FIELD_DIM_X - 1) || j != (CELL_FIELD_DIM_Y - 1))
                    {   
                        if ((right == SIGNAL_OUT_1 
                        ||   right == WIRE_VERTICAL 
                        ||   right == NOT_GATE 
                        ||   right == WIRE_CORNER_LEFT
                        ||   right == WIRE_CORNER_RIGHT) 

                        &&  
                            (left == GATE_INPUT))
                            valid = true;
                    }
                    break;
                
                case NOT_GATE:
                case WIRE_VERTICAL:
                    if (i != 0 || i != (CELL_FIELD_DIM_X - 1))
                    {
                        if ((right == SIGNAL_OUT_1 
                        ||   right == WIRE_VERTICAL 
                        ||   right == NOT_GATE 
                        ||   right == WIRE_CORNER_LEFT
                        ||   right == WIRE_CORNER_RIGHT)

                        &&  
                            (left == SIGNAL_IN_A 
                        ||   left == SIGNAL_IN_B
                        ||   left == SIGNAL_IN_C
                        ||   left == SIGNAL_IN_D
                        ||   left == SIGNAL_IN_E
                        ||   left == SIGNAL_IN_F 
                        ||   left == SIGNAL_IN_G
                        ||   left == OR_GATE
                        ||   left == AND_GATE
                        ||   left == NOT_GATE
                        ||   left == WIRE_VERTICAL ))
                            valid = true;
                    }
                    break;

                case WIRE_HORIZONTAL:
                    if (i != 0 || j != 0 || i != (CELL_FIELD_DIM_X - 1) || j != (CELL_FIELD_DIM_Y - 1))
                    {
                        if ((top == WIRE_CORNER_LEFT
                        ||   top == WIRE_HORIZONTAL
                        ||   top == GATE_INPUT)
                        
                        &&
                            (bottom == WIRE_CORNER_RIGHT
                        ||   bottom == WIRE_HORIZONTAL
                        ||   bottom == GATE_INPUT))
                            valid = true;
                    }
                    break;    
                
                case GATE_INPUT:
                    if (i != 0 || j != 0 || i != (CELL_FIELD_DIM_X - 1) || j != (CELL_FIELD_DIM_Y - 1))
                    {
                        if ((right == OR_GATE
                        ||   right == AND_GATE)
                        
                        &&
                            (top == WIRE_CORNER_LEFT
                        ||   top == WIRE_HORIZONTAL)
                        
                        &&
                            (bottom == WIRE_CORNER_RIGHT
                        ||   bottom == WIRE_HORIZONTAL))
                            valid = true;
                    }
                    break;

                case WIRE_CORNER_LEFT:
                    if (i != 0 || i != (CELL_FIELD_DIM_X - 1) || j != (CELL_FIELD_DIM_Y - 1))
                    {
                        if ((left == SIGNAL_IN_A 
                        ||   left == SIGNAL_IN_B
                        ||   left == SIGNAL_IN_C
                        ||   left == SIGNAL_IN_D
                        ||   left == SIGNAL_IN_E
                        ||   left == SIGNAL_IN_F 
                        ||   left == SIGNAL_IN_G
                        ||   left == OR_GATE
                        ||   left == AND_GATE
                        ||   left == NOT_GATE
                        ||   left == WIRE_VERTICAL)
                        
                        &&
                            (bottom == WIRE_CORNER_RIGHT
                        ||   bottom == WIRE_HORIZONTAL
                        ||   bottom == GATE_INPUT))
                            valid = true;
                    }
                    break;

                case WIRE_CORNER_RIGHT:
                    if (i != 0 || j != 0 || i != (CELL_FIELD_DIM_X - 1))
                    {
                        if ((left == SIGNAL_IN_A 
                        ||   left == SIGNAL_IN_B
                        ||   left == SIGNAL_IN_C
                        ||   left == SIGNAL_IN_D
                        ||   left == SIGNAL_IN_E
                        ||   left == SIGNAL_IN_F 
                        ||   left == SIGNAL_IN_G
                        ||   left == OR_GATE
                        ||   left == AND_GATE
                        ||   left == NOT_GATE
                        ||   left == WIRE_VERTICAL)
                        
                        &&
                            (top == WIRE_CORNER_LEFT
                        ||   top == WIRE_HORIZONTAL
                        ||   top == GATE_INPUT))
                            valid = true;
                    }
                    break;
                    
                case SIGNAL_IN_A:
                case SIGNAL_IN_B:
                case SIGNAL_IN_C:
                case SIGNAL_IN_D:
                case SIGNAL_IN_E:
                case SIGNAL_IN_F:
                case SIGNAL_IN_G:
                    if (i != (CELL_FIELD_DIM_X - 1))
                    {
                        if ((right == SIGNAL_OUT_1 
                        ||   right == WIRE_VERTICAL 
                        ||   right == NOT_GATE 
                        ||   right == WIRE_CORNER_LEFT
                        ||   right == WIRE_CORNER_RIGHT))
                            valid = true;
                    }
                    break;
                
                case SIGNAL_OUT_1:
                    if (i != 0)
                    {
                        if  (left == SIGNAL_IN_A 
                        ||   left == SIGNAL_IN_B
                        ||   left == SIGNAL_IN_C
                        ||   left == SIGNAL_IN_D
                        ||   left == SIGNAL_IN_E
                        ||   left == SIGNAL_IN_F 
                        ||   left == SIGNAL_IN_G
                        ||   left == OR_GATE
                        ||   left == AND_GATE
                        ||   left == NOT_GATE
                        ||   left == WIRE_VERTICAL)
                            valid = true;
                    }
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
                result.replace(1, 1, generateExpression(x_ - 1, y_, true));
                result.replace(result.size() - 2, 1, generateExpression(x_ - 1, y_, false));
                break;
            
            case AND_GATE:
                result = " * ";
                result.replace(0, 1, generateExpression(x_ - 1, y_, true));
                result.replace(result.size() - 1, 1, generateExpression(x_ - 1, y_, false));
                break;

            case NOT_GATE:
                result = "( )'";
                result.replace(1, 1, generateExpression(x_ - 1, y_));
                break;

        // CONNECTION WIRE
            case GATE_INPUT:
            case WIRE_HORIZONTAL:
                result = (checkUpward_ ? generateExpression(x_, y_ - 1, true) : generateExpression(x_, y_ + 1, false));
                break;

            case WIRE_CORNER_LEFT:
            case WIRE_CORNER_RIGHT:
            case WIRE_VERTICAL:
                result = generateExpression(x_ - 1, y_);
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