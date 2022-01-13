#include "Program.hpp"

int main()
{
    // Hide terminal
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    Program program;

    while (program.running())
    {
        program.update();
        program.render();
    }
    return 0;
}