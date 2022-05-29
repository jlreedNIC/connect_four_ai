#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <algorithm>

class AgentConnect4
{
    public:
        AgentConnect4();
        ~AgentConnect4();

        int pickMove(int arrBoard[][7]);

    private:
        int maxValue(int state[][7], int move, int depth);
        int minValue(int state[][7], int move, int depth);

        // checking for a win
        // functions copied from textApp.h
        // find something more efficient
        int checkForWin(int arrBoard[][7]);
        int horizWinCheck(int arrBoard[][7], int i, int j, int winstate);
        int vertWinCheck(int arrBoard[][7], int i, int j, int winstate);
        int diagWinCheck(int arrBoard[][7], int i, int j, int winstate);

        void placeToken(int arrBoard[][7], int player, int position);

        bool checkForDraw(int arrBoard[][7]);


        int maxDepth;

};


#endif