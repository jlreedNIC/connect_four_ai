/**
 * @file environment.h
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief Declaration file for the environment. This contains the gameboard
 *        and the relevant functions to act on the gameboard.
 * 
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream> // debugging so far

class Environment
{
    public:
        Environment();
        Environment(int** otherGameBoard);
        Environment(const Environment &gameState);
        ~Environment();

        void operator= (const Environment &that); // pretty sure this is not needed

        int** getBoard();   // is this function needed?
        // think about printing gameboard instead, or returning string with values
        // or maybe return board[i][j] just for gui sake?

        int checkForWin();
        int checkForWin(const int &player);
        int placeToken(const int &player, const int &position); // return -1 if placing token was unsuccessful
        bool checkForDraw();

    private:
        int **board; // board made up of 1's (computer), 0's (empty), and -1's (opponent)
                         // 6 rows, 7 columns
        
        int horizWinCheck(const int &player, const int &i, const int &j);
        int vertWinCheck(const int &player, const int &i, const int &j);
        int diagWinCheck(const int &player, const int &i, const int &j);

        
};


#endif