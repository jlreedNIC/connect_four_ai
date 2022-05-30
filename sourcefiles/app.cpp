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
{
    // constructor
    std::cout << "app constructor called\n";
    window.setPosition(sf::Vector2i(50,50)); // TO DO: look at how to set relative to each computer

    position = 0; // cursor column location
    whoStarts = 1;

    // initialize cursor
    cursor.setPointCount(3);
    cursor.setRadius(25.f);
    cursor.setFillColor(sf::Color::Green);
    cursor.setRotation(180.f);
    cursor.setPosition(sf::Vector2f(115.f, 60.f));

    // initialize board background
    boardBackground.setFillColor(sf::Color::Blue);
    // set position of rectangle to middle of window
    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    float rectWidth = width - 100;
    float rectHeight = height - 100;
    boardBackground.setSize(sf::Vector2f(rectWidth, rectHeight));
    
    boardBackground.setOrigin(sf::Vector2f(rectWidth/2, rectHeight/2));
    boardBackground.setPosition(sf::Vector2f(width/2, (height/10)* 5.5));

    // initialize board holes
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<7; j++)
        {
            boardHoles[i][j].setRadius(25.f);
            boardHoles[i][j].setFillColor(sf::Color::White);
            boardHoles[i][j].move(sf::Vector2f(j*70 + 65, i*80 + 100));
        }
    }
    
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
    while(window.isOpen()) // && checkForWin() == 0)
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
                        // placeToken(1);
                        std::cout << "placing token\n";
                    }
                    break;
                default:
                    break;
            }
        }

        // if(checkForWin() != 0)
        // {
        //     // function for displaying winner
        //     std::cout << "we have a winner!\n";
            
        // }

        window.clear(sf::Color::White);

        // draw things
        drawGameBoard(); // board & cursor
        window.display();

    }
}

void App::drawGameBoard()
{
    window.draw(boardBackground);
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            window.draw(boardHoles[i][j]);

    window.draw(cursor);
}

void App::moveCursor(const sf::Keyboard::Key &direction)
{    
    sf::Vector2f moveVector(0.f, 0.f);

    if(direction == sf::Keyboard::Left && position > 0)
    {
        moveVector.x -= 70.f;
        position--;
    }
    if(direction == sf::Keyboard::Right && position < 6)
    {
        moveVector.x += 70.f;
        position++;
    }
    cursor.move(moveVector);

    std::cout << "cursor over " << position << "\n";
    
}
