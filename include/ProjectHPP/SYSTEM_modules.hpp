#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <stack>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern const int CELL_FIELD_DIM_X;
extern const int CELL_FIELD_DIM_Y;

extern const int CELL_SIZE;

enum CellType : unsigned char 
{
    EMPTY_CELL = 10,
    OR_GATE,
    AND_GATE,
    NOT_GATE,

    GATE_INPUT,
    WIRE_CORNER_LEFT,
    WIRE_CORNER_RIGHT,
    WIRE_HORIZONTAL,
    WIRE_VERTICAL,

    SIGNAL_IN_A,
    SIGNAL_IN_B,
    SIGNAL_IN_C,
    SIGNAL_IN_D,
    SIGNAL_IN_E,
    SIGNAL_IN_F,
    SIGNAL_IN_G,

    SIGNAL_OUT_1,
    SIGNAL_OUT_2,
    SIGNAL_OUT_3
};