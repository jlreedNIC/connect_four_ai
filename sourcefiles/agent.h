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

        int pickMove(int **gameBoard);
        void reorderMoves(const int &value);

    private:
        int maxDepth;
        int winValue;
        int errorValue;
        int moveOrder[7];

        // helper functions for alpha beta pruning
        int abMaxValue(Environment gameState, const int &move, const int &depth, int bestMinValue, int bestMaxValue);
        int abMinValue(Environment gameState, const int &move, const int &depth, int bestMinValue, int bestMaxValue);

        int evaluate(Environment &gameState);
        int horizWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int vertWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int posDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);
        int negDiagWeight(Environment &gameState, const int &row, const int &column, const int &player);

};

#endif