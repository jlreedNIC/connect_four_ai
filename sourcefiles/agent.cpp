/**
 * @file agent.cpp
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief Definition file for agent class.
 * 
 */

#include "agent.h"

/**
 * @brief Construct a new Agent object. Sets the winValue, errorValue, and maxDepth.
 * 
 */
Agent::Agent()
{
    maxDepth = 7; 
    winValue = 10000;
    errorValue = winValue*winValue;

    for(int i=0; i<7; i++)
    {
        moveOrder[i] = i;
    }
    // std::cout << "Agent created\n";
}

Agent::~Agent()
{
    // std::cout << "Agent Destroyed\n";
}

/**
 * @brief Picks the best move for the agent to make on the given gameboard based off of minmax searching. 
 * 
 * @param gameBoard Current state of the gameboard
 * @return int move agent should make
 */
int Agent::pickMove(int **gameBoard)
{
    Environment gameState = gameBoard;
    
    int value = -winValue;
    int bestValue = -winValue;
    int bestMove = 0;
    // maxDepth++; // maybe implement with alphabeta pruning

    int alpha = -winValue, beta = winValue;
    // find max of every child (which is min node)
    for(int i=0; i<7; i++)
    {
        value = abMinValue(gameState, i, 1, beta, alpha);
        if(value == -1) // error, don't go here
        {
            if(bestMove < 6) bestMove++;
            bestValue = errorValue*-1;            
        }
        else if(value > bestValue) // finding max of min nodes
        {
            bestValue = value;
            bestMove = moveOrder[i];
        }
    }
    reorderMoves(bestMove); // will now check last move made first
    return bestMove;
}

/**
 * @brief Puts the given value at the start of the move array, and moves 
 *        the other values up one. Makes the assumption that the value IS in the array.
 * 
 * @param value int from 0 - 6
 */
void Agent::reorderMoves(const int &value)
{
    int tempIndex = 0, tempVal = 0, swapVal = 0;

    // find index of value
    for(int i=0; i<7; i++)
    {
        if(moveOrder[i] == value)
        {
            tempIndex = i;
            break;
        }
    }

    // put value in first slot and move everything else up
    swapVal = moveOrder[0];
    moveOrder[0] = moveOrder[tempIndex];

    for(int i=1; i<=tempIndex; i++)
    {
        tempVal = moveOrder[i];
        moveOrder[i] = swapVal;
        swapVal = tempVal;
    }
}

/**
 * @brief Using alpha beta pruning, return the maximum of the next move options.
 * 
 * @param gameState current board configuration
 * @param move move to make on board
 * @param depth current depth of search tree
 * @param bestMinValue also known as beta, the current best value on the min tree
 * @param bestMaxValue also known as alpha, the current best value of the max tree
 * @return int maximum value of all choices
 */
int Agent::abMaxValue(Environment gameState, const int &move, const int &depth, int bestMinValue, int bestMaxValue)
{
    // apply move to state
    int result = gameState.placeToken(-1, move);
    if(result == -1)
        return errorValue;

    // check for win or loss
    int value = gameState.checkForWin();
    if(value != 0) return (winValue*value)+(value*depth);
    
    // draw
    if(gameState.checkForDraw()) return 0;

    // leaf node
    if(depth == maxDepth) return evaluate(gameState);

    value = -winValue + depth;
    // check max of every next state = min state
    for(int i=0; i<7; i++)
    {
        value = std::max(value, abMinValue(gameState, i, depth+1, bestMinValue, bestMaxValue));
        if(value >= bestMinValue)
        {
            // std::cout << " max ab value found: " << value << "\n";
            return value;
        }
        else
        {
            bestMaxValue = std::max(value, bestMaxValue);
        }
    }
    return value;
}

/**
 * @brief Using alpha beta pruning, return the minimum of the next move options.
 * 
 * @param gameState current board configuration
 * @param move move to make on the board
 * @param depth current depth of search tree
 * @param bestMinValue also known as beta, the current best value on the min tree
 * @param bestMaxValue also known as alpha, the current best value of the max tree
 * @return int minimum value of all choices
 */
int Agent::abMinValue(Environment gameState, const int &move, const int &depth, int bestMinValue, int bestMaxValue)
{
    // std::cout << "checking abmin node" << move << "...\n";
    int result = gameState.placeToken(1, move);
    if(result == -1)
        return errorValue*-1;

    // win or loss
    int value = gameState.checkForWin();
    if(value != 0) return (winValue*value)+(value*depth);
    
    // draw
    if(gameState.checkForDraw()) return 0;

    // leaf node
    if(depth == maxDepth) return evaluate(gameState);

    value = winValue-depth;
    // checking next states
    for(int i=0; i<7; i++)
    {
        value = std::min(value, abMaxValue(gameState, i, depth+1, bestMinValue, bestMaxValue));
        if(value <= bestMaxValue)
        {
            // std::cout << " minimum ab value found: " << value << "\n";
            return value;
        }
        else
        {
            bestMinValue = std::min(value, bestMinValue);
        }
    }
    return value;
}

/**
 * @brief Assigns a value to each node based off of the tokens in a row containing that node.
 *        Adds the weight from the computer, subtracts the weight from the player.
 *        Calculates the weights according to the horizontal, vertical, and both diagonals.
 * 
 * @param gameState Board configuration to give a weight to.
 * @return int weight (or score) of the board based on how many tokens in a row, plus how many available spaces
 */
int Agent::evaluate(Environment &gameState)
{
    int weight = 0;
    /*
    count how many in a row
        reach end
        count how many empty
        add the 2
        if 4, then weight = fill*5 + empty*2
        else 0
    */
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            weight += horizWeight(gameState, i, j, 1);
            weight -= horizWeight(gameState, i, j, -1);

            weight += vertWeight(gameState, i, j, 1);
            weight -= vertWeight(gameState, i, j, -1);

            weight += posDiagWeight(gameState, i, j, 1);
            weight -= posDiagWeight(gameState, i, j, -1);

            weight += negDiagWeight(gameState, i, j, 1);
            weight -= negDiagWeight(gameState, i, j, -1);
        }
    }
    // std::cout << "total weight: " << weight << "\n";
    return weight;
}

/**
 * @brief gives a weight for the specific token based on the horizontal checks.
 * 
 * @param gameState Board configuration to check
 * @param row Row position of the specific node
 * @param column Column position of the specific node
 * @param player which player to check for, 1 or -1
 * @return int weight based on how many squares are filled and empty, or 0 if no possible win
 */
int Agent::horizWeight(Environment &gameState, const int &row, const int &column, const int &player)
{
    int end=0, ex=0, ey=0; // checking ends
    int pj = 0, nj = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

    // checks the board position passed in and adds to appropriate count
    if(board[row][column] == player) amtTokens++;
    else if(board[row][column] == 0) amtEmpty++;
    else
    {
        if(column == 3) return 0;
        else if(column < 3) ex = 1;
        else ey = 1;
    }

    pj = column + 1;
    nj = column - 1;
    while(end < 2)
    {
        // count in positive direction until end of board found or end of available space found
        if(ey == 0 && pj < 7 && board[row][pj] == player)
            amtTokens++;

        if(ey == 0 && pj < 7 && board[row][pj] == 0)
            amtEmpty++;

        if(pj >= 7 || board[row][pj] == (player*-1))
            ey = 1;

        // count in negative direction until end of board found or end of available space found
        if(ex == 0 && nj >= 0 && board[row][nj] == player)
            amtTokens++;
        if(ex == 0 && nj >= 0 && board[row][nj] == 0)
            amtEmpty++;
        if(nj < 0 || board[row][nj] == (player*-1))
            ex = 1;
        
        end = ex+ey;
        pj++;
        nj--;
    }
    // if 4 tokens in a row, return a win!
    if(amtTokens >= 4)
        return winValue;
    
    // count available spaces
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4) // if not enough spaces to win, return 0
        return 0;
    else // return weighting function
    {
        return (amtTokens*5) + (amtEmpty*2);
    }
}

/**
 * @brief gives a weight for the specific token based on the vertical checks.
 * 
 * @param gameState Board configuration to check
 * @param row Row position of the specific node
 * @param column Column position of the specific node
 * @param player which player to check for, 1 or -1
 * @return int weight based on how many squares are filled and empty, or 0 if no possible win
 */
int Agent::vertWeight(Environment &gameState, const int &row, const int &column, const int &player)
{
    int end=0, ex=0, ey=0; // checking ends
    int pi = 0, ni = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

    // checks the board position passed in and adds to appropriate count
    if(board[row][column] == player) amtTokens++;
    else if(board[row][column] == 0) amtEmpty++;
    else 
    {
        if(row < 3) ex = 1;
        else ey = 1;
    }

    pi = column + 1;
    ni = column - 1;
    while(end < 2)
    {
        // count in positive direction until end of board found or end of available space found
        if(ey == 0 && pi < 6 && board[pi][column] == player)
            amtTokens++;

        if(ey == 0 && pi < 6 && board[pi][column] == 0)
            amtEmpty++;

        if(pi >= 6 || board[pi][column] == (player*-1))
            ey = 1;

        // count in negative direction until end of board found or end of available space found
        if(ex == 0 && ni >= 0 && board[ni][column] == player)
            amtTokens++;
        if(ex == 0 && ni >= 0 && board[ni][column] == 0)
            amtEmpty++;
        if(ni < 0 || board[ni][column] == (player*-1))
            ex = 1;
        
        end = ex+ey;
        pi++;
        ni--;
    }
    // if 4 tokens in a row, return win
    if(amtTokens >= 4)
        return winValue;
    
    // count available spaces
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4) // if not enough spaces to win, return 0
        return 0;
    else // return weighting function
    {
        return (amtTokens*5) + (amtEmpty*2);
    }
}

/**
 * @brief gives a weight for the specific token based on the diagonal with a positive slope
 * 
 * @param gameState Board configuration to check
 * @param row Row position of the specific node
 * @param column Column position of the specific node
 * @param player which player to check for, 1 or -1
 * @return int weight based on how many squares are filled and empty, or 0 if no possible win
 */
int Agent::posDiagWeight(Environment &gameState, const int &row, const int &column, const int &player)
{
    int end=0, ex=0, ey=0; // checking ends
    int pi = 0, ni = 0;
    int pj = 0, nj = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

    // checks the board position passed in and adds to appropriate count
    if(board[row][column] == player) amtTokens++;
    else if(board[row][column] == 0) amtEmpty++;
    else 
    {
        if(column < 4 && row > 2) ex = 1;
        else ey = 1;
    }

    pi = column + 1;
    pj = row + 1;
    ni = column - 1;
    nj = row - 1;
    while(end < 2)
    {
        // count in positive direction until end of board found or end of available space found
        if(ey == 0 && ni >= 0 && pj < 7 && board[ni][pj] == player)
            amtTokens++;

        if(ey == 0 && ni >= 0 && pj < 7 && board[ni][pj] == 0)
            amtEmpty++;

        if(ni < 0 || pj >= 7 || board[ni][pj] == (player*-1))
            ey = 1;

        // count in negative direction until end of board found or end of available space found
        if(ex == 0 && pi < 6 && nj >= 0 && board[pi][nj] == player)
            amtTokens++;
        if(ex == 0 && pi < 6 && nj >= 0 && board[pi][nj] == 0)
            amtEmpty++;
        if(pi >= 6 || nj < 0 || board[pi][nj] == (player*-1))
            ex = 1;
        
        end = ex+ey;
        pi++;
        pj++;
        ni--;
        nj--;
        
    }
    // if 4 tokens in a row, return a win!
    if(amtTokens >= 4)
        return winValue;
    
    // count available spaces
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4) // if not enough spaces to win, return 0
        return 0;
    else // return weighting function
    {
        return (amtTokens*5) + (amtEmpty*2);
    }
}

/**
 * @brief gives a weight for the specific token based on the diagonal with a negative slope
 * 
 * @param gameState Board configuration to check
 * @param row Row position of the specific node
 * @param column Column position of the specific node
 * @param player which player to check for, 1 or -1
 * @return int weight based on how many squares are filled and empty, or 0 if no possible win
 */
int Agent::negDiagWeight(Environment &gameState, const int &row, const int &column, const int &player)
{
    int end=0, ex=0, ey=0; // checking ends
    int pi = 0, ni = 0;
    int pj = 0, nj = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

    // checks the board position passed in and adds to appropriate count
    if(board[row][column] == player) amtTokens++;
    else if(board[row][column] == 0) amtEmpty++;
    else 
    {
        if(column > 2 && row > 2) ey = 1;
        else ex = 1;
    }

    pi = column + 1;
    pj = row + 1;
    ni = column - 1;
    nj = row - 1;
    while(end < 2)
    {
        // count in positive direction until end of board found or end of available space found
        if(ey == 0 && pi < 6 && pj < 7 && board[pi][pj] == player)
            amtTokens++;

        if(ey == 0 && pi < 6 && pj < 7 && board[pi][pj] == 0)
            amtEmpty++;

        if(pi >= 6 || pj >= 7 || board[pi][pj] == (player*-1))
            ey = 1;

        // count in negative direction until end of board found or end of available space found
        if(ex == 0 && ni >= 0 && nj >= 0 && board[ni][nj] == player)
            amtTokens++;
        if(ex == 0 && ni >= 0 && nj >= 0 && board[ni][nj] == 0)
            amtEmpty++;
        if(ni < 0 || nj < 0 || board[ni][nj] == (player*-1))
            ex = 1;
        
        end = ex+ey;
        pi++;
        pj++;
        ni--;
        nj--;
    }
    // if 4 tokens in a row, return a win!
    if(amtTokens >= 4)
        return winValue;
    
    // count available spaces
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4) // if not enough spaces to win, return 0
        return 0;
    else // return weighting function
    {
        return (amtTokens*5) + (amtEmpty*2);
    }
}
