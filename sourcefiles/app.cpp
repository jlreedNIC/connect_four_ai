/**
 * @file app.cpp
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 05-25-22
 * @class
 * @brief 
 * 
 */

#include "app.h"

App::App() : window(sf::VideoMode(600,600), "Connect Four AI Test")
            //  cursor(25.f, 3)
{
    // constructor
    std::cout << "app constructor called\n";
    window.setPosition(sf::Vector2i(50,50)); // TO DO: look at how to set relative to each computer

    cursorPos.x = 100.f;
    cursorPos.y = 50.f;
    position = 0; // this is causing stack smashing, but I don't know why
    // potential problem found of needing to update SFML
    // maybe reinstall sfml?
    whoStarts = 1;

    for(int i=0; i<7; i++)
        for(int j=0; j<6; j++)
            boardNum[i][j] = 0;
    
    // std::cout << "tried cursor setting up\n";
}

App::~App()
{
    // destructor
    std::cout << "app destructor called\n";
}

void App::startMenu()
{
    // while(window.isOpen())
    // {
    //     sf::Event event;

    //     while(window.pollEvent(event))
    //     {
    //         if(event.type == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    //         {
    //             std::cout << "Mouse button pushed\n";
    //         }
    //     }

    //     drawStartMenu();
    // }
}

// void App::drawStartMenu()
// {
//     sf::RectangleShape playerFirst(sf::Vector2f(50.f, 30.f));
//     playerFirst.setFillColor(sf::Color::White);
//     playerFirst.setOutlineColor(sf::Color::Black);
// }

void App::runApp()
{
    while(window.isOpen() && checkForWin() == 0)
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            // std::cout << "started polling\n";
            // sf::Keyboard::Key key;
            // handle events
            switch(event.type)
            {
                case sf::Event::Closed:
                    std::cout << "closing window\n";
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    // std::cout << "key pressed\n";
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        moveCursor(sf::Keyboard::Left);
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        moveCursor(sf::Keyboard::Right);
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    {
                        placeToken(1);
                    }
                    break;
                default:
                    break;
            }
            // std::cout << "entered polling loop\n";
            // if(event.type == sf::Event::Closed)
            // {
            //     std::cout << "closing window\n";
            //     window.close();
            // }
        }

        if(checkForWin() != 0)
        {
            // function for displaying winner
            std::cout << "we have a winner!\n";
            
        }

        window.clear(sf::Color::White);

        // draw things
        drawGameBoard(); // board
        drawCursor();

        window.display();

    }
}

void App::drawGameBoard()
{
    // set position of rectangle to middle of window
    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    float rectWidth = width - 100;
    float rectHeight = height - 100;
    sf::RectangleShape board(sf::Vector2f(rectWidth, rectHeight));
    board.setFillColor(sf::Color::Blue);
    
    board.setOrigin(sf::Vector2f(rectWidth/2, rectHeight/2));
    board.setPosition(sf::Vector2f(width/2, (height/10)* 5.5));
    window.draw(board);

    sf::CircleShape boardHoles[7][6];
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<6; j++)
        {
            boardHoles[i][j].setRadius(25.f);
            if(boardNum[i][j] == 0)
                boardHoles[i][j].setFillColor(sf::Color::White);
            else if(boardNum[i][j] == 1)
                boardHoles[i][j].setFillColor(sf::Color::Green);
            else boardHoles[i][j].setFillColor(sf::Color::Magenta);
            // boardHoles[i][j].setFillColor(sf::Color::White);
            boardHoles[i][j].move(sf::Vector2f(i*70 + 65, j*80 + 100));
            window.draw(boardHoles[i][j]);
        }
    }
    // std::cout << "drawing cursor\n";
    // window.draw(cursor);
    // std::cout << "drawing cursor succeeded\n";
}

void App::moveCursor(const sf::Keyboard::Key &direction)
{
    // cursor.setRadius(25.f);
    // cursor.setPointCount(3);
    
    // sf::Vector2f moveVector(0.f, 0.f);

    if(direction == sf::Keyboard::Left && position > 0)
    {
        cursorPos.x -= 70.f;
        position--;
    }
    if(direction == sf::Keyboard::Right && position < 6)
    {
        cursorPos.x += 70.f;
        position++;
    }

    // std::cout << "cursor over " << position << "\n";
    
}

void App::drawCursor()
{
    sf::CircleShape cursor(25.f, 3);
    cursor.setOrigin(sf::Vector2f(25/2, 25/2));
    cursor.setFillColor(sf::Color::Green);
    cursor.setPosition(cursorPos);
    cursor.setRotation(180.f);

    // cursor.move(moveVector);
    window.draw(cursor);
}

void App::placeToken(int player)
{
    int j = 0;
    // place at end of column
    for(j=0; j<6; j++)
    {
        if(boardNum[position][j] != 0)
        {
            break;
        }
    }
    j--;
    if(j >= 0)
    {
        boardNum[position][j] = player;
    }
}

int App::checkForWin()
{
    int winStates[] = {-1, 1};
    int win = 0;

    for(int i=0; i<7; i++)
    {
        for(int j=0; j<6; j++)
        {
            for(int k=0; k<2; k++)
            {
                if(boardNum[i][j] == winStates[k])
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

int App::horizWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pi = i+1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pi < 6 && boardNum[pi][j] == winstate)
            count++;
        else ex = 1;

        if(ni >= 0 && boardNum[ni][j] == winstate)
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

int App::vertWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int nj = j-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && boardNum[i][pj] == winstate)
            count++;
        else ex = 1;

        if(nj >= 0 && boardNum[i][nj] == winstate)
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

int App::diagWinCheck(int i, int j, int winstate)
{
    int count = 1;
    int pj = j+1;
    int pi = i+1;
    int nj = j-1;
    int ni = i-1;
    int end=0, ex=0, ey=0;

    do
    {
        if(pj < 7 && pi < 6 && boardNum[pi][pj] == winstate)
            count++;
        else ex = 1;

        if(nj >= 0 && ni >= 0 && boardNum[ni][nj] == winstate)
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
