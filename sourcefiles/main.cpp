/**
 * @file main.cpp
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 05-25-22
 * @class
 * @brief 
 * 
 */

#include <iostream>
#include "app.h"

int main()
{
    std::cout << "hello world\n";

    App connect4app;
    connect4app.runApp();

    std::cout << "window crashed?\n";
    std::cout << "guess not.\n";

    // sf::RenderWindow window(sf::VideoMode(600, 600), "testing window");

    // while(window.isOpen())
    // {
    //     sf::Event event;
    //     while(window.pollEvent(event))
    //     {
    //         if(event.type == sf::Event::Closed)
    //         {
    //             std::cout << "closing window\n";
    //             window.close();
    //         }
    //     }

    //     window.clear(sf::Color::White);

    //     window.display();

        
    // }

    return 0;
}