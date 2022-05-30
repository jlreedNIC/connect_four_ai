#ifndef TEXTAPP_H
#define TEXTAPP_H

#include <iostream>
#include <iomanip>
#include <string>
#include "agent.h"
#include "environment.h"

class Connect4App
{
    public:
        Connect4App();
        ~Connect4App();

        void startMenu();
        void gameLoop();

    private:
        int cursor;
        int whoStarts;

        void printGameBoard();

        void exitScreen();


        Agent gameAgent;
        Environment gameBoard;
};


#endif