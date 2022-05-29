#include "textApp.h"


Connect4App::Connect4App() : gameAgent()
{
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            board[i][j] = 0;
        }
    }

    cursor = 3;
    // board[0][0] = -1;
    // board[1][1] = 1;
    // board[2][2] = 1; 
    // board[3][3] = 1; 
    // board[0][5] = -1; 
    // board[0][6] = -1;

    // board[1][0] = 1;
    // board[1][1] = 1;
    // board[1][2] = -1;
    // board[1][3] = 1;
    // board[1][4] = 0;
    // board[1][5] = -1;
    // board[1][6] = -1; 
    // board[2][6] = -1;
    // board[3][6] = -1;

    // board = {{0, 1, 1, 1, -1, -1, -1},
    //          {1, 1, 1, 1, 0, -1, -1},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0},
    //          {0, 0, 0, 0, 0, 0, 0}};


    start = 1;

}

Connect4App::~Connect4App()
{
    std::cout << "game class stopped\n";
}

void Connect4App::startMenu()
{
    char choice = '0';
    
    do
    {
        std::cout << "\nWho will start?\n";
        std::cout << " (1) Computer\n";
        std::cout << " (2) Player\n";
        std::cout << " (0) Exit\n";
        std::cin >> choice;

        switch(choice)
        {
            case '0':
                exitScreen();
                break;
            case '1':
                start = 1;
                choice = '0';
                std::cout << "Computer starts\n";
                break;
            case '2':
                start = -1;
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
    char choice = '1';

    // printGameBoard();
    // std::cout << checkForWin() << "\n";
    while(checkForWin() == 0 && choice != '0')
    {
        printGameBoard();

        // player turn
        // handled by start variable
        if(start == -1)
        {
            std::cout << "Player's turn\n";
            std::cout << "\n (1) Move left (2) Move right (3) Place token (0) Exit\n";
            std::cin >> choice;
            std::cout << "You entered " << choice << "\n";

            if(choice == '1' && cursor > 0)
            {
                cursor--;
            }
            if(choice == '2' && cursor < 6)
                cursor++;
            
            if(choice == '3')
            {
                placeToken(start);
                start = 1;
                // std::cout << "placed\n";
            }
            
            
        }

        // computer option
        else if(start == 1)
        {
            // std::cout << "computer going\n";
            // gameAgent.pickMove(board);
            cursor = gameAgent.pickMove(board);
            placeToken(1);
            // std::cout << "Computer's turn\n";
            // std::cout << "\n (1) Move left (2) Move right (3) Place token (0) Exit\n";
            // std::cin >> choice;
            // std::cout << "You entered " << choice << "\n";

            // if(choice == '1' && cursor > 0)
            // {
            //     cursor--;
            // }
            // if(choice == '2' && cursor < 6)
            //     cursor++;
            
            // if(choice == '3')
            // {
            //     placeToken(start);
                start = -1;
                cursor = 3;
            //     // std::cout << "placed\n";
            // }



            // cursor = computer pick space
            // placeToken(start);
            // cursor = 3;
            
        }
        if(choice == '0')
            exitScreen();
        
    }
    int winner = checkForWin();
    if(winner != 0)
        std::cout << "We have a winner! " << winner << "\n";
    printGameBoard();
}

void Connect4App::placeToken(int player)
{
    int j = 0;
    // place at end of column
    for(j=0; j<6; j++)
    {
        if(board[j][cursor] != 0)
        {
            break;
        }
    }
    j--;
    if(j >= 0)
    {
        board[j][cursor] = player;
    }
}

void Connect4App::exitScreen()
{
    std::cout << "Thanks for playing!\n";
    // exit(0);
}

void Connect4App::printGameBoard()
{
    std::string emptyspace = "   ";
    for(int i=0; i<4*cursor; i++)
        emptyspace += " ";

    // system("clear");
    std::cout << emptyspace << "V\n";
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
                    {
                        // std::cout << "horizontal win!\n";
                        return win;
                    }
                    win = vertWinCheck(i,j,winStates[k]);
                    if(win != 0)
                    {
                        // std::cout << "vertical win!\n";
                        return win;
                    }
                    win = diagWinCheck(i,j,winStates[k]);
                    if(win != 0)
                    {
                        // std::cout << "diagonal win!\n";
                        return win;
                    }
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
        if(pi < 6 && board[pi][j] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(ni >= 0 && board[ni][j] == winstate && ey == 0)
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

int Connect4App::vertWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int nj = j-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && board[i][pj] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && board[i][nj] == winstate && ey ==0)
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
        if(pj < 7 && pi < 6 && board[pi][pj] == winstate && ex ==0)
            count++;
        else ex = 1;

        if(nj >= 0 && ni >= 0 && board[ni][nj] == winstate && ey ==0)
        {
            // std::cout << board[ni][nj] << "board[" << ni << "][" << nj << "]\n";
            count++;
        }
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
