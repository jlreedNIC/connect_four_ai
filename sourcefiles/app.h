/**
 * @file app.h
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief The class declarations for the GUI portion of the connect four game.
 *        Also contains the environment and agent variables.
 * 
 */

#ifndef APP_H
#define APP_H

#include <iostream> // debugging
#include <unistd.h> // sleep function
#include <SFML/Graphics.hpp>
#include "environment.h"
#include "agent.h"

class App
{
    public:
        App();
        ~App();

        void startMenu();
        void runApp();

    private:
        sf::RenderWindow window;
        sf::CircleShape cursor;
        sf::RectangleShape boardBackground;
        sf::CircleShape boardHoles[6][7];

        sf::Font basicFont;                 // font for text
        sf::Text instructions;              // text to display at the beginning and end of game
        sf::RectangleShape background;      // background popup for the end of the game

        void setText(); // initialize text for start screen

        void drawGameBoard(); // draw game board
        void exitScreen(); 

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