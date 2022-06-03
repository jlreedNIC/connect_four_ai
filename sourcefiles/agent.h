/**
 * @file agent.h
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief Declaration file for agent class. Agent is in charge of trying to pick
 *        the winning solution against the opponent.
 * 
 */

#ifndef AGENT_H
#define AGENT_H

#include <iostream> // for debugging
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

        // TO DO: fix alpha beta pruning. try selective ordering or another method to add to it.
        int abMaxValue(Environment gameState, const int &move, const int &depth, int &bestMinValue, int &bestMaxValue);
        int abMinValue(Environment gameState, const int &move, const int &depth, int &bestMinValue, int &bestMaxValue);

        int evaluate(Environment &gameState);
        int horizWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int vertWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int posDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int negDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);

};

#endif