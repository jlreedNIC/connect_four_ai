#include "textApp.h"


Connect4App::Connect4App() : gameAgent(), gameBoard()
{
    cursor = 3;
    whoStarts = 1;

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
                whoStarts = 1;
                choice = '0';
                std::cout << "Computer starts\n";
                break;
            case '2':
                whoStarts = -1;
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
    while(gameBoard.checkForWin() == 0 && choice != '0')
    {
        printGameBoard();

        // player turn
        // handled by start variable
        if(whoStarts == -1)
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
                gameBoard.placeToken(-1, cursor);
                whoStarts = 1;
                // std::cout << "placed\n";
            }
            
            
        }

        // computer option
        else if(whoStarts == 1)
        {
            // std::cout << "computer going\n";
            // gameAgent.pickMove(board);
            cursor = gameAgent.pickMove(gameBoard.getBoard());
            gameBoard.placeToken(1, cursor);
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
                whoStarts = -1;
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
    int winner = gameBoard.checkForWin();
    if(winner != 0)
        std::cout << "We have a winner! " << winner << "\n";
    printGameBoard();
}

void Connect4App::exitScreen()
{
    std::cout << "Thanks for playing!\n";
    // system("exit");
    // exit(0);
}

void Connect4App::printGameBoard()
{
    // int** tempBoard = gameBoard.getBoard();
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
            std::cout << " |" << std::setw(2) << gameBoard.getBoard()[i][j];
        }
        std::cout << " |\n";
    }
    std::cout << " ----------------------------- \n";
}

