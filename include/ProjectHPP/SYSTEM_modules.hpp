#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <map>
#include <stack>
#include <windows.h>

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

    SIGNAL_OUT,
};

enum ExitFlag : unsigned char
{
    GO_TO_TYPEIN = 50,
    GO_TO_GRAPHIC,
    GO_TO_OUTPUT,
    GO_TO_MENU
};

enum CurrentState : unsigned char
{
    MENU_STATE = 100,
    TYPEIN_STATE,
    GRAPHIC_STATE,
    OUTPUT_STATE
};