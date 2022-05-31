#include "agent.h"

/**
 * @brief Construct a new Agent object. Sets the winValue, errorValue, and maxDepth.
 * 
 */
Agent::Agent()
{
    maxDepth = 4; 
    winValue = 1000;
    errorValue = winValue*10;
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
    
    int value = 0;
    int bestValue = -winValue;
    int bestMove = 0;
    // maxDepth++; // maybe implement with alphabeta pruning

    // call max of every state
    for(int i=0; i<7; i++)
    {
        // std::cout << "\nstarting minmax search for max node " << i << "\n";
        value = minValue(gameState, i, 1); // might be min value function...not sure
        if(value == -1) 
        {
            // std::cout << "not this root node\n";
            if(bestMove < 7) bestMove++;
            bestValue = errorValue*-1;
            // std::cout << "bestval: " << bestValue << " bestmove: " << bestMove << "\n";
            
        }
        else if(value > bestValue)
        {
            bestValue = value;
            bestMove = i;
            // std::cout << "best move found " << bestMove << " " << i << "\n";
        }
        // std::cout << "value: " << value << " best value: " << bestValue << "\n";
    }
    // std::cout << "best move: " << bestMove << "\n";
    return bestMove;
}

/**
 * @brief Gives the minimum value of all of the possible choices, which are all maximum nodes or
 *        a win, loss, draw, or evaluation of the state
 * 
 * @param gameState board configuration
 * @param move potential next move to make
 * @param depth current depth of search tree
 * @return int minimum of all choices
 */
int Agent::minValue(Environment gameState, int move, int depth)
{
    // gamestate should be temporary variable (not passed by reference)

    // std::cout << "checking min node" << move << "...\n";
    int result = gameState.placeToken(1, move);
    // std::cout << "placing token result" << result << "\n";
    if(result == -1)
        return -1;

    // win or loss
    int value = gameState.checkForWin();
    // std::cout << "win value " << value << "\n";
    
    // if(value != 0)
    // {
    //     for(int i=0; i<6; i++)
    //     {
    //         for(int j=0; j<7; j++)
    //             std::cout << gameState.getBoard()[i][j] << " ";
    //         std::cout << "\n";
    //     }
    // }

    if(value != 0)
    {
        // std::cout << "returning: " << (winValue*value)+(value*depth) << "\n";
        return (winValue*value)+(value*depth);
    }

    
    if(gameState.checkForDraw())
    {
        // std::cout << "returning 0\n";
        return 0;
    }

    // leaf node
    if(depth == maxDepth)
    {
        // std::cout << "calling eval function\n";
        // std::cout << "returning 0\n";
        return evaluate(gameState);;
    }

    value = winValue - depth;
    int bestValue = winValue-depth;
    // std::cout << "bestvalue: " << bestValue << "\n";
    int bestMove = 0;
    // checking next states
    for(int i=0; i<7; i++)
    {
        value = std::min(value, maxValue(gameState, i, depth+1));
        if(value == -1) 
        {
            // std::cout << "not this min node\n";
            if(bestMove < 7) bestMove++;
            // std::cout << "best Value: " << bestValue << " move: " << bestMove << "\n";
        }
        else if(value < bestValue)
        {
            bestValue = value;
            bestMove = i;
        }
    }
    // std::cout << "min: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
}

/**
 * @brief Gives the maximum value of all of the possible choices, which are all minimum nodes or
 *        a win, loss, draw, or evaluation of the state
 * 
 * @param gameState board configuration
 * @param move potential next move to make
 * @param depth current depth of search tree
 * @return int maximum of all choices
 */
int Agent::maxValue(Environment gameState, int move, int depth)
{
    // gamestate should be temporary variable (not passed by reference)

    // std::cout << "checking max node " << move << "...\n";

    // apply move to state
    int result = gameState.placeToken(-1, move);
    // std::cout << "placing token result" << result << "\n";
    if(result == -1)
        return 1;

    // check for loss
    int value = gameState.checkForWin();
    // std::cout << "win value " << value << "\n";
    
    // for(int i=0; i<6; i++)
    // {
    //     for(int j=0; j<7; j++)
    //         std::cout << gameState.getBoard()[i][j] << " ";
    //     std::cout << "\n";
    // }

    if(value != 0)
    {
        // std::cout << "returning: " << (winValue*value)+(value*depth) << "\n";
        return (winValue*value)+(value*depth);
    }
    
    if(gameState.checkForDraw())
    {
        // std::cout << "returning 0\n";
        return 0;
    }

    // leaf node
    if(depth == maxDepth)
    {
        // std::cout << "calling eval function\n";
        // std::cout << "returning 0\n";
        return evaluate(gameState);;
    }

    value = -winValue + depth;
    int bestValue = -winValue + depth;
    
    int bestMove = 0;
    // check max of every next state = min state
    for(int i=0; i<7; i++)
    {
        value = std::max(value, minValue(gameState, i, depth+1));
        if(value == -1) 
        {
            // std::cout << "not this max node\n";
            if(bestMove <7) bestMove++;
        }
        else if(value > bestValue)
        {
            bestValue = value;
            bestMove = i;
        }
    }
    // std::cout << "max: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
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
        // positive direction
        if(ey == 0 && pj < 7 && board[row][pj] == player)
            amtTokens++;

        if(ey == 0 && pj < 7 && board[row][pj] == 0)
            amtEmpty++;

        if(pj >= 7 || board[row][pj] == (player*-1))
            ey = 1;

        // negative direction
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
    if(amtTokens >= 4)
        return winValue;
    
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4)
        return 0;
    else
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
        // positive direction
        if(ey == 0 && pi < 6 && board[pi][column] == player)
            amtTokens++;

        if(ey == 0 && pi < 6 && board[pi][column] == 0)
            amtEmpty++;

        if(pi >= 6 || board[pi][column] == (player*-1))
            ey = 1;

        // negative direction
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
    if(amtTokens >= 4)
        return winValue;
    
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4)
        return 0;
    else
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
    // std::cout << "Starting posdiagweight check\n";
    int end=0, ex=0, ey=0; // checking ends
    int pi = 0, ni = 0;
    int pj = 0, nj = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

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
        // positive direction
        if(ey == 0 && ni >= 0 && pj < 7 && board[ni][pj] == player)
            amtTokens++;

        if(ey == 0 && ni >= 0 && pj < 7 && board[ni][pj] == 0)
            amtEmpty++;

        if(ni < 0 || pj >= 7 || board[ni][pj] == (player*-1))
            ey = 1;

        // negative direction
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
    if(amtTokens >= 4)
        return winValue;
    
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4)
        return 0;
    else
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
    // std::cout << "Starting negdiagweight check\n";
    int end=0, ex=0, ey=0; // checking ends
    int pi = 0, ni = 0;
    int pj = 0, nj = 0;
    int amtTokens = 0, amtEmpty = 0;
    int amtAvail = 0; // available space to win

    int** board = gameState.getBoard();

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
        // positive direction
        if(ey == 0 && pi < 6 && pj < 7 && board[pi][pj] == player)
            amtTokens++;

        if(ey == 0 && pi < 6 && pj < 7 && board[pi][pj] == 0)
            amtEmpty++;

        if(pi >= 6 || pj >= 7 || board[pi][pj] == (player*-1))
            ey = 1;

        // negative direction
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
    if(amtTokens >= 4)
        return winValue;
    
    amtAvail = amtTokens + amtEmpty;
    if(amtAvail < 4)
        return 0;
    else
    {
        return (amtTokens*5) + (amtEmpty*2);
    }
}

