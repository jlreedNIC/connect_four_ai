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
#include <SFML/Graphics.hpp>
// #include <SFML/Keyboard.hpp>

class App
{
    public:
        App();
        ~App();

        void runApp();

    private:
        sf::RenderWindow window;
        // sf::CircleShape cursor;
        sf::Vector2f cursorPos;

        void drawGameBoard();
        // void drawCursor(const int &direction=-1);
        void moveCursor(const sf::Keyboard::Key &direction=sf::Keyboard::Unknown);
        void drawCursor();

        int position; // where in the board to put a token

        

};



#endif