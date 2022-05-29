#include "agent.h"

AgentConnect4::AgentConnect4()
{
    std::cout << "agent created\n";

    maxDepth = 2;
}

AgentConnect4::~AgentConnect4()
{
    std::cout << "agent destroyed\n";
}

int AgentConnect4::pickMove(int arrBoard[][7])
{
    int tempBoard[6][7];
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            tempBoard[i][j] = arrBoard[i][j];

    
    int value = 0;
    int bestValue = -1000;
    int bestMove = 0;
    // call max (every state)
    for(int i=0; i<7; i++)
    {
        // std::cout << "starting minmax search...\n";
        value = minValue(tempBoard, i, 1); // might be min value function...not sure
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

int AgentConnect4::maxValue(int state[][7], int move, int depth)
{
    int tempArray[6][7];
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            tempArray[i][j] = state[i][j];

    // std::cout << "checking max node for move " << move << "...\n";
    int value = 0;
    placeToken(tempArray, -1, move);

    // win or loss
    value = checkForWin(tempArray);
    // std::cout << "win value: " << value << "\n";
    if(value != 0)
    {
        // std::cout << "returning: " << (value*1000) + (value*depth) << "\n";
        return (value*1000) + (value*depth);
    }
    
    if(checkForDraw(tempArray))
    {
        // std::cout << "returning 0\n";
        return 0;
    }

    if(depth == maxDepth)
    {
        // std::cout << "calling eval function\n";
        // std::cout << "returning 0\n";
        return 0;
    }

    value = 1000 - depth;
    int bestValue = 1000 - depth;
    int bestMove = 0;
    for(int i=0; i<7; i++)
    {
        value = std::max(value, minValue(tempArray, i, depth+1));
        if(value > bestValue)
        {
            bestValue = value;
            bestMove = i;
        }
    }
    // std::cout << "max: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
}

int AgentConnect4::minValue(int state[][7], int move, int depth)
{
    int tempArray[6][7];
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            tempArray[i][j] = state[i][j];

    // std::cout << "checking min node for " << move << "...\n";
    int value = 0;
    placeToken(tempArray, 1, move);

    // win or loss
    value = checkForWin(tempArray);
    // std::cout << "win value " << value << "\n";
    if(value != 0)
    {
        // std::cout << "returning: " << (value*1000) + (value*depth) << "\n";
        return (value*1000) + (value*depth);
    }
    
    if(checkForDraw(tempArray))
    {
        // std::cout << "returning 0\n";
        return 0;
    }

    if(depth == maxDepth)
    {
        // std::cout << "calling eval function\n";
        // std::cout << "returning 0\n";
        return 0;
    }

    value = 1000 - depth;
    int bestValue = 1000-depth;
    int bestMove = 0;
    for(int i=0; i<7; i++)
    {
        value = std::min(value, maxValue(tempArray, i, depth+1));
        if(value < bestValue)
        {
            bestValue = value;
            bestMove = i;
        }
    }
    // std::cout << "min: " << value << " bestValue: " << bestValue << " move: " << bestMove << "\n";
    return bestValue;
}

int AgentConnect4::checkForWin(int arrBoard[][7])
{
    int winStates[] = {-1, 1};
    int win = 0;

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            for(int k=0; k<2; k++)
            {
                if(arrBoard[i][j] == winStates[k])
                {
                    // std::cout << "Checking for win " << i << j << winStates[k] << "...\n";
                    win = horizWinCheck(arrBoard, i,j,winStates[k]);
                    if(win != 0)
                        return win;
                    win = vertWinCheck(arrBoard, i,j,winStates[k]);
                    if(win != 0)
                        return win;
                    win = diagWinCheck(arrBoard, i,j,winStates[k]);
                    if(win != 0)
                        return win;
                }
            }
        }
    }
    return win;
}

int AgentConnect4::horizWinCheck(int arrBoard[][7], int i, int j, int winstate)
{
    int count = 1;
    int pi = i+1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pi < 6 && arrBoard[pi][j] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(ni >= 0 && arrBoard[ni][j] == winstate && ey == 0)
            count++;
        else ey = 1;

        pi++;
        ni--;
        end = ex + ey;

        // std::cout << count << "\n";
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return winstate;
}

int AgentConnect4::vertWinCheck(int arrBoard[][7], int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int nj = j-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && arrBoard[i][pj] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && arrBoard[i][nj] == winstate && ey ==0)
            count++;
        else ey = 1;

        pj++;
        nj--;
        end = ex + ey;
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return winstate;
}

int AgentConnect4::diagWinCheck(int arrBoard[][7], int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int pi = i+1;
    int nj = j-1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && pi < 6 && arrBoard[pi][pj] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && ni >= 0 && arrBoard[ni][nj] == winstate && ey ==0)
            count++;
        else ey = 1;

        pj++;
        pi++;
        nj--;
        ni--;
        end = ex + ey;
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return winstate;
}

void AgentConnect4::placeToken(int arrBoard[][7], int player, int position)
{
    int j = 0;
    // place at end of column
    for(j=0; j<6; j++)
    {
        if(arrBoard[j][position] != 0)
        {
            break;
        }
    }
    j--;
    if(j >= 0)
    {
        arrBoard[j][position] = player;
    }

    // return arrBoard;
}

bool AgentConnect4::checkForDraw(int arrBoard[][7])
{
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            if(arrBoard[i][j] == 0)
                return false;
    
    return true;
}