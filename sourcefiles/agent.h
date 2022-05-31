#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <algorithm> // for min and max functions
#include "environment.h"

class Agent
{
    public:
        Agent();
        ~Agent();

        int pickMove(int **gameBoard); // instead of gameBoard, do environment or assign gameboard values to new environment

    private:
        int maxDepth;
        int winValue;
        int errorValue;

        // helper functions for pickMove
        int maxValue(Environment gameState, const int &move, const int &depth);
        int minValue(Environment gameState, const int &move, const int &depth);

        int abMaxValue(Environment gameState, const int &bestMinValue, const int &move, const int &depth);
        int abMinValue(Environment gameState, const int &bestMaxValue, const int &move, const int &depth);

        int evaluate(Environment &gameState);
        int horizWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int vertWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int posDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int negDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);

};

#endif