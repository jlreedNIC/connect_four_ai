#include "textApp.h"


Connect4App::Connect4App()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            board[i][j] = 0;
        }
    }
    board[0][0] = -1;
    board[1][1] = 1;
    board[2][2] = 1; 
    board[3][3] = 1; 
    board[0][5] = -1; 
    board[0][6] = -1;

    board[1][0] = 1;
    board[1][1] = 1;
    board[1][2] = -1;
    board[1][3] = 1;
    board[1][4] = 0;
    board[1][5] = -1;
    board[1][6] = -1; 
    board[2][6] = -1;
    board[3][6] = -1;

    // board = {{0, 1, 1, 1, -1, -1, -1},
    //          {1, 1, 1, 1, 0, -1, -1},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0}};


    start = 0;

}

Connect4App::~Connect4App()
{

}

void Connect4App::startMenu()
{
    char choice = '0';
    
    do
    {
        std::cout << "Who will start?\n";
        std::cout << " (1) Computer\n";
        std::cout << " (2) Player\n";
        std::cout << " (0) Exit\n";
        std::cin >> choice;

        switch(choice)
        {
            case '0':
                std::cout << "Thanks for playing\n";
                break;
            case '1':
                start = 0;
                choice = '0';
                std::cout << "Computer starts\n";
                break;
            case '2':
                start = 1;
                choice = '0';
                std::cout << "Player starts\n";
                break;
            default:
                std::cout << "Invalid answer. Try again.\n";
                break;
        }

    }while(choice != '0');

}

void Connect4App::gameLoop()
{
    printGameBoard();
    std::cout << checkForWin() << "\n";
    // while(checkForWin())
    // {
    //     printGameBoard();
    // }
}

void Connect4App::printGameBoard()
{
    std::cout << " ----------------------------- \n";
    for(int i=0; i<6; i++)
    {
        
        for(int j=0; j<7; j++)
        {
            std::cout << " |" << std::setw(2) << board[i][j];
        }
        std::cout << " |\n";
    }
    std::cout << " ----------------------------- \n";
}

int Connect4App::checkForWin()
{
    int count = 0;
    int winStates[] = {-1, 1};
    int win = 0;

    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            for(int k=0; k<2; k++)
            {
                if(board[i][j] == winStates[k])
                {
                    // std::cout << "Checking for win " << i << j << winStates[k] << "...\n";
                    win = horizWinCheck(i,j,winStates[k]);
                    if(win != 0)
                        return win;
                    win = vertWinCheck(i,j,winStates[k]);
                    if(win != 0)
                        return win;
                    win = diagWinCheck(i,j,winStates[k]);
                    if(win != 0)
                        return win;
                }
            }
        }
    }
    return win;
}

int Connect4App::horizWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pi = i+1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pi < 7 && board[pi][j] == winstate)
            count++;
        else ex = 1;

        if(ni >= 0 && board[ni][j] == winstate)
            count++;
        else ey = 1;

        pi++;
        ni--;
        end = ex + ey;
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return winstate;
}

int Connect4App::vertWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int nj = j-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 6 && board[i][pj] == winstate)
            count++;
        else ex = 1;

        if(nj >= 0 && board[i][nj] == winstate)
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

int Connect4App::diagWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int pi = i+1;
    int nj = j-1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 6 && pi < 7 && board[pi][pj] == winstate)
            count++;
        else ex = 1;

        if(nj >= 0 && ni >= 0 && board[ni][nj] == winstate)
            count++;
        else ey = 1;

        pj++;
        pi++;
        nj--;
        ni++;
        end = ex + ey;
    }while(count < 4 && end < 2);

    if(count < 4)
        return 0;
    else return winstate;
}

// int Connect4App::checkHorizWin()
// {
//     int compWin = 0;
//     int playerWin = 0;
//     int win = 0;
//     int i=0, j=0, k=0;

//     for(j=0; j<6; j++)
//     {
//         for(i=0; i<7; i++)
//         {
//             if(board[j][i] == 1)
//             {
//                 // check next 3
//                 for(k=i+1; k<i+4; k++)
//                 {
//                     win = 1;
//                     if(k > 6 || board[j][k] != 1)
//                     {
//                         i = k;
//                         win = 0;
//                         break;
//                     }
//                 }
//             }
            
//             if(board[j][i] == -1)
//             {
//                 for(k=i+1; k<i+4; k++)
//                 {
//                     win = -1;
//                     if(k > 6 || board[j][k] != -1)
//                     {
//                         i = k;
//                         win = 0;
//                         break;
//                     }
//                 }
//             }

//             if(win != 0)
//                 break;
//         }

//         if(win != 0)
//             break;
//     }

//     if(win != 0)
//     {
//         std::cout << "We have a winnner." << i << j << k << win << "\n";
//     }

//     return win;

// }