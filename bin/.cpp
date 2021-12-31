void BoolExpression::check_ValidNeighboringCells()
{
    for (short i = 0; i < NUM_CELLS; ++i)
    {
        for (short j = 0; j < NUM_CELLS; ++j)
        {
            if (cells[i][j]->getCurrentType() != EMPTY_CELL)
            {    
                valid = false;
                switch (cells[i][j]->getCurrentType())
                {
                case OR_GATE:
                case AND_GATE:
                    if (cells[i][++j]->getCurrentType() == SIGNAL_OUT_1 
                    ||  cells[i][++j]->getCurrentType() == WIRE_VERTICAL 
                    ||  cells[i][++j]->getCurrentType() == NOT_GATE 
                    ||  cells[i][++j]->getCurrentType() == WIRE_CORNER_LEFT
                    ||  cells[i][++j]->getCurrentType() == WIRE_CORNER_RIGHT)
                        valid = true;
                    
                    if (cells[--i][j]->getCurrentType() == SIGNAL_IN_A 
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_B
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_C
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_D
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_E
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_F 
                    ||  cells[--i][j]->getCurrentType() == SIGNAL_IN_G
                    ||  cells[--i][j]->getCurrentType() == WIRE_CORNER_RIGHT
                    ||  cells[--i][j]->getCurrentType() == EMPTY_CELL)
                        valid = true;

                    if (cells[i][--j]->getCurrentType() == GATE_INPUT)
                        valid = true;

                    if (cells[++i][j]->getCurrentType() == SIGNAL_IN_A 
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_B
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_C
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_D
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_E
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_F 
                    ||  cells[++i][j]->getCurrentType() == SIGNAL_IN_G
                    ||  cells[++i][j]->getCurrentType() == WIRE_CORNER_LEFT
                    ||  cells[++i][j]->getCurrentType() == EMPTY_CELL)
                        valid = true;
                    break;
                
                case NOT_GATE:
                case WIRE_VERTICAL:

                default:
                    break;}
            }   
        }
        
    }
}