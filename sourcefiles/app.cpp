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
    position = 0;
    
    // std::cout << "tried cursor setting up\n";
}

App::~App()
{
    // destructor
    std::cout << "app destructor called\n";
}

void App::runApp()
{
    while(window.isOpen())
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
                    std::cout << "key pressed\n";
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        moveCursor(sf::Keyboard::Left);
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        moveCursor(sf::Keyboard::Right);
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
            boardHoles[i][j].setFillColor(sf::Color::White);
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
