#include "Program.hpp"

int main()
{
    Program program;

    while (program.running())
    {
        program.update();
        program.render();
    }
    return 0;
}