#include "agent.h"

Agent::Agent()
{
    maxDepth = 4; 
    // std::cout << "Agent created\n";
}

Agent::~Agent()
{
    // std::cout << "Agent Destroyed\n";
}

int Agent::pickMove(int **gameBoard)
{
    Environment gameState = gameBoard;
    
    int value = 0;
    int bestValue = -1000;
    int bestMove = 0;

    // call max of every state
    for(int i=0; i<7; i++)
    {
        // std::cout << "starting minmax search...\n";
        value = minValue(gameState, i, 1); // might be min value function...not sure
        if(value > bestValue)
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

int Agent::minValue(Environment gameState, int move, int depth)
{
    // gamestate should be temporary variable (not passed by reference)

    // std::cout << "checking min node for " << move << "...\n";
    gameState.placeToken(1, move);

    // loss
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
        // std::cout << "returning: " << (1000*value)+(value*depth) << "\n";
        return (1000*value)+(value*depth);
    }

    // win
    // value = gameState.checkForWin(1);
    // if(value == 1)
    //     return 1000+depth;
    
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
        return 0;
    }

    value = 1000 - depth;
    int bestValue = 1000-depth;
    int bestMove = 0;
    // checking next states
    for(int i=0; i<7; i++)
    {
        value = std::min(value, maxValue(gameState, i, depth+1));
        if(value < bestValue)
        {
            bestValue = value;
            bestMove = i;
        }
    }
    // std::cout << "min: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
}

int Agent::maxValue(Environment gameState, int move, int depth)
{
    // gamestate should be temporary variable (not passed by reference)

    // std::cout << "checking max node for move " << move << "...\n";

    // apply move to state
    // TO DO: need to handle if error
    gameState.placeToken(-1, move);

    // check for loss
    int value = gameState.checkForWin(-1);
    // std::cout << "win value: " << value << "\n";
    if(value == -1)
        return -1000-depth;
    
    // check for win
    value = gameState.checkForWin(1);
    // std::cout << "win value: " << value << "\n";
    if(value == 1)
        return 1000+depth;
    
    // check for draw
    if(gameState.checkForDraw())
    {
        // std::cout << "returning 0\n";
        return 0;
    }
    
    // will need to call evaluation function
    if(depth == maxDepth)
    {
        // std::cout << "calling eval function\n";
        // std::cout << "returning 0\n";
        return 0;
    }

    value = 1000 - depth;
    int bestValue = 1000 - depth;
    // int bestMove = 0;
    // check max of every next state = min state
    for(int i=0; i<7; i++)
    {
        value = std::max(value, minValue(gameState, i, depth+1));
        if(value > bestValue)
        {
            bestValue = value;
            // bestMove = i;
        }
    }
    // std::cout << "max: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
}
