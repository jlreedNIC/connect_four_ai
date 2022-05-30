/**
 * @file app.h
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 05-25-22
 * @class
 * @brief 
 * 
 */

#ifndef APP_H
#define APP_H


#include <iostream>
#include <unistd.h> // sleep function
#include <SFML/Graphics.hpp>
#include "environment.h"
#include "agent.h"
// #include <SFML/Keyboard.hpp>

class App
{
    public:
        App();
        ~App();

        void runApp();
        void startMenu();

    private:
        sf::RenderWindow window;
        sf::CircleShape cursor;
        sf::RectangleShape boardBackground;
        sf::CircleShape boardHoles[6][7];

        void drawGameBoard();
        void exitScreen();
        // void drawCursor(const int &direction=-1);
        void moveCursor(const sf::Keyboard::Key &direction=sf::Keyboard::Unknown);
        void updateGameBoard();
        void updateCursor();

        // board variables and functions
        int position; // column position of cursor
        int whoStarts; // 1 for computer, -1 for opponent

        Environment gameBoard;
        Agent agent;        

};



#endif