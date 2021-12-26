#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <stack>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int NUM_CELLS;
extern int CELL_SIZE;

enum CellType : unsigned char 
{
    OR_GATE = 10,
    AND_GATE,
    NOT_GATE,

    Gate_INPUT,
    Gate_INPUT_LEFT,
    Gate_INPUT_RIGHT,

    SIGNAL_A,
    SIGNAL_B,
    SIGNAL_C,
};

enum MouseClick : unsigned char
{
    LEFT,
    MIDDLE,
    RIGHT,
};