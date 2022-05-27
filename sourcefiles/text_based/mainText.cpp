

#include <iostream>
#include "textApp.h"

int main()
{
    Connect4App app;

    app.startMenu();
    app.gameLoop();

    return 0;
}