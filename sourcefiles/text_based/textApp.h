#ifndef TEXTAPP_H
#define TEXTAPP_H

#include <iostream>
#include <iomanip>

class Connect4App
{
    public:
        Connect4App();
        ~Connect4App();

        void startMenu();
        void gameLoop();

    private:
        int board[6][7]; // 1 for comp, -1 for player
        int start;

        void printGameBoard();

        int checkForWin();
        int horizWinCheck(int i, int j, int winstate);
        int vertWinCheck(int i, int j, int winstate);
        int diagWinCheck(int i, int j, int winstate);
};


#endif