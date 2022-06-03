/**
 * @file environment.cpp
 * @author Jordan Reed (jlreed@students.nic.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief Definition file for the environment class.
 * 
 */

#include "environment.h"

/**
 * @brief Default constructor. Dynamically allocates new 2d array for the board.
 * 
 */
Environment::Environment()
{
    board = new int*[6];
    for(int i=0; i<6; i++)
        board[i] = new int[7];

    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            board[i][j] = 0;
    
    // std::cout << "memory created\n";

}

/**
 * @brief Construct a new Environment out of a given array
 * 
 * @param otherGameBoard dynamic array to copy
 */
Environment::Environment(int** otherGameBoard)
{
    board = new int*[6];
    for(int i=0; i<6; i++)
        board[i] = new int[7];

    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            board[i][j] = otherGameBoard[i][j];
    
    // std::cout << "other constructor called\n";
}

/**
 * @brief copy constructor
 * 
 * @param gameState environment object to copy
 */
Environment::Environment(const Environment &gameState)
{
    // something about copy constructor not being called in -std=c++17
    board = new int*[6];
    for(int i=0; i<6; i++)
        board[i] = new int[7];

    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            board[i][j] = gameState.board[i][j];
    
    // std::cout << "copy constructor called\n";
}

/**
 * @brief Destroy the environment. Deallocates memory.
 * 
 */
Environment::~Environment()
{
    for(int i=0; i<6; i++)
        delete [] board[i];
    
    delete [] board;

    // std::cout << "memory deleted\n";
}

/**
 * @brief Returns the board variable for use in gui applications.
 * 
 * @return int** Address of 2d array, board variable.
 */
int** Environment::getBoard()
{
    return board;
}

/**
 * @brief Places a token for the correct player at the first available spot in the column.
 *        If unable to place token, returns error.
 * 
 * @param player Who's turn is it. 1 for computer, -1 for opponenet
 * @param position Which column to place a token in
 * @return int -1 on fail, 0 on successful placement
 */
int Environment::placeToken(const int &player, const int &position)
{
    int success = 0;
    int j = 0;
    // place at end of column
    for(j=0; j<6; j++)
    {
        if(board[j][position] != 0)
        {
            break;
        }
    }
    j--;
    if(j >= 0)
    {
        board[j][position] = player;
    }
    else success = -1;

    return success;
}

/**
 * @brief Checks for a draw by checking every spot in the gameboard. 
 *        If there is a spot not filled, there is not a draw. Does
 *        not check for win configurations. Literally just checks for
 *        a full board.
 * 
 * @return true If board is full
 * @return false If there is an empty spot in board
 */
bool Environment::checkForDraw() // rename checkEmptyBoard?
{
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            if(board[i][j] == 0)
                return false;
    
    return true;
}

/**
 * @brief Checks the board for a winning configuration for either the player or the computer
 * 
 * @return int 1 if the computer won, -1 if the player won, or 0 if neither
 */
int Environment::checkForWin()
{
    int win = checkForWin(1);
    if(win == 1)
        return win;
    win = checkForWin(-1);
    if(win == -1)
        return win;
    return 0;
}

/**
 * @brief Checks the board for a winning configuration for the given player.
 *        First checks the horizontal, then vertical, then the diagonals.
 * 
 * @param player Who to check the win for, 1 for computer, -1 for opponent
 * @return int 0 for no win, -1 for opponent win, 1 for computer win
 */
int Environment::checkForWin(const int &player)
{
    int win = 0;

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(board[i][j] == player)
            {
                // std::cout << "Checking for win " << i << j << winStates[k] << "...\n";
                win = horizWinCheck(player, i, j);
                if(win != 0)
                {
                    // std::cout << "horizontal win!\n";
                    return win;
                }
                win = vertWinCheck(player, i, j);
                if(win != 0)
                {
                    // std::cout << "vertical win!\n";
                    return win;
                }
                win = diagWinCheck(player, i, j);
                if(win != 0)
                {
                    // std::cout << "diagonal win!\n";
                    return win;
                }
            }
        }
    }
    return win;
}

/**
 * @brief Checks the neighboring cells in the horizontal direction to see if 
 *        there are 4 tokens in a row.
 * 
 * @param player 1 for computer, -1 for opponent; token to check for
 * @param i row of board
 * @param j column of board
 * @return int 0 if no win connected to this cell, 1 if computer win, -1 for player win
 */
int Environment::horizWinCheck(const int &player, const int &i, const int &j)
{
    int count = 1; // how many tokens in a row
    int pi = i+1; // positive i value
    int ni = i-1; // negative i value
    int end=0, ex=0, ey=0; // end, end of x, end of y

    // check each direction of the token row
    // if you reach the end of that token, ex = 1
    // else keep counting number of tokens in a row
    do
    {
        if(pi < 6 && board[pi][j] == player && ex ==0)
            count++;
        else ex = 1;

        if(ni >= 0 && board[ni][j] == player && ey == 0)
            count++;
        else ey = 1;

        pi++;
        ni--;
        end = ex + ey;

        // std::cout << count << "\n";
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return player;
}

/**
 * @brief Checks the neighboring cells in the vertical direction to see if 
 *        there are 4 tokens in a row.
 * 
 * @param player 1 for computer, -1 for opponent; token to check for
 * @param i row of board
 * @param j column of board
 * @return int 0 if no win connected to this cell, 1 if computer win, -1 for player win
 */
int Environment::vertWinCheck(const int &player, const int &i, const int &j)
{
    int count = 1;
    int pj = j+1;
    int nj = j-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && board[i][pj] == player && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && board[i][nj] == player && ey ==0)
            count++;
        else ey = 1;

        pj++;
        nj--;
        end = ex + ey;
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return player;
}

/**
 * @brief Checks the neighboring cells in each diagonal direction to see
 *        if there are 4 in a row
 * 
 * @param player 1 for computer, -1 for opponent; token to check for
 * @param i row of board
 * @param j column of board
 * @return int 0 if no win connected to this cell, 1 if computer win, -1 for player win
 */
int Environment::diagWinCheck(const int &player, const int &i, const int &j)
{
    int count = 1;
    int pj = j+1;
    int pi = i+1;
    int nj = j-1;
    int ni = i-1;
    int end=0, ex=0, ey=0;
    int otherEnd=0, oex=0, oey=0; // for other diagonal
    int otherCount = 1;           // for other diagonal

    do
    {
        // negative slope diagonal
        if(pj < 7 && pi < 6 && board[pi][pj] == player && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && ni >= 0 && board[ni][nj] == player && ey ==0)
        {
            // std::cout << board[ni][nj] << "board[" << ni << "][" << nj << "]\n";
            count++;
        }
        else ey = 1;

        // positive slope diagonal
        if(pj < 7 && ni >= 0 && board[ni][pj] == player && oex == 0)
        {
            otherCount++;
        }
        else oex = 1;

        if(nj >= 0 && pi < 6 && board[pi][nj] == player && oey == 0)
        {
            otherCount++;
        }
        else oey = 1;

        pj++;
        pi++;
        nj--;
        ni--;
        end = ex + ey;
        otherEnd = oex + oey;
    }while((count < 4 && end < 2) || (otherCount < 4 && otherEnd < 2));

    if(count < 4 && otherCount < 4)
        return 0;
    else return player;
}
