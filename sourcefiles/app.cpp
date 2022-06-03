/**
 * @file app.cpp
 * @author Jordan Reed (reed5204@vandals.uidaho.edu)
 * @date 06-03-22
 * @class CS 470
 * @brief Definition file for the app class. 
 * 
 */

#include "app.h"

/**
 * @brief Construct a new App object. Creates the gameboard, the agent, and
 *        the graphics for the game. 
 * 
 */
App::App() : window(sf::VideoMode(600,600), "Connect Four AI Test"), gameBoard(), agent()
{
    // constructor
    // std::cout << "app constructor called\n";
    window.setPosition(sf::Vector2i(50,50)); // TO DO: look at how to set relative to each computer

    position = 3; // cursor column location
    whoStarts = -1;

    // initialize cursor
    cursor.setPointCount(3);
    cursor.setRadius(25.f);
    cursor.setFillColor(sf::Color::Black);

    // initialize board background
    boardBackground.setFillColor(sf::Color::Blue);
    // set position of rectangle to middle of window
    sf::Vector2u size = window.getSize();

    float rectWidth = size.x - 100;
    float rectHeight = size.y - 100;
    boardBackground.setSize(sf::Vector2f(rectWidth, rectHeight));
    
    boardBackground.setOrigin(sf::Vector2f(rectWidth/2, rectHeight/2));
    boardBackground.setPosition(sf::Vector2f(size.x/2, (size.y/10)* 5.5));

    // background for exit screen
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(3);
    background.setSize(sf::Vector2f(size.x - 200, size.y - 400));
    background.setOrigin(sf::Vector2f((size.x-200)/2, (size.y-400)/2));
    background.setPosition(sf::Vector2f(size.x/2, size.y/2));

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
    
    if(!basicFont.loadFromFile("sourcefiles/fonts/Roboto-Thin.ttf"))
    {
        std::cerr << "error loading font\n";
    }

    setText();
}

/**
 * @brief Initializes the text and starting cursor for use in the start menu.
 * 
 */
void App::setText()
{
    sf::Vector2f position(180.f, 100.f);

    cursor.setRotation(90.f);
    cursor.setPosition(position.x+20.f, position.y+80.f);

    instructions.setFont(basicFont);
    instructions.setFillColor(sf::Color::Black);
    instructions.setCharacterSize(36);
    instructions.setString("Who will go first? \n\n    Computer \n    Player");
    instructions.setPosition(position);
}

/**
 * @brief Destroys the App
 * 
 */
App::~App()
{
    // destructor
    // std::cout << "app destructor called\n";
}

/**
 * @brief Pops up a start menu so players can choose who goes first
 * 
 */
void App::startMenu()
{
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                std::cout << "closing window\n";
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && cursor.getPosition().y == 180.f)
                {
                    cursor.move(sf::Vector2f(0.0f, 45.f));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && cursor.getPosition().y == 225.f)
                {
                    cursor.move(sf::Vector2f(0.0f, -45.f));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    std::cout << "checking position of cursor to set who starts\n";
                    if(cursor.getPosition().y == 180.f) whoStarts = 1;
                    else whoStarts = -1;
                    return;
                }
            }
        }

        // draw window
        window.clear(sf::Color::White);
        window.draw(instructions);
        window.draw(cursor);
        window.display();
    }
}

/**
 * @brief Main game loop. Responsible for changing turns and drawing the game board.
 * 
 */
void App::runApp()
{
    // reset cursor to right position
    cursor.setPosition(sf::Vector2f(325.f, 60.f));
    cursor.setRotation(180.f);

    // draw board once so if computer takes turn, it doesn't take forever to show up
    window.clear(sf::Color::White);
    drawGameBoard(); // board & cursor
    window.display();

    while(window.isOpen())
    {
        if(whoStarts == -1)
        {
            // player starts
            sf::Event event;
            
            while(window.pollEvent(event))
            {
                // handle events
                switch(event.type)
                {
                    case sf::Event::Closed:
                        std::cout << "closing window\n";
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
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
                            int result = gameBoard.placeToken(-1, position);
                            if(result == -1)
                            {
                                std::cout << "invalid column. Try again.\n";
                            }
                            else
                            {
                                whoStarts = 1;
                                std::cout << "placing token\n";
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            // computer turn
            int tokenPosition = agent.pickMove(gameBoard.getBoard());
            gameBoard.placeToken(1, tokenPosition);
            std::cout << "computer chose " << tokenPosition << "\n";

            whoStarts = -1;
        }

        updateGameBoard();
        updateCursor();
        
        window.clear(sf::Color::White);

        // draw things
        drawGameBoard(); // board & cursor
        window.display();

        int winner = gameBoard.checkForWin();
        bool draw = gameBoard.checkForDraw();
        if(winner != 0 || draw)
        {
            // function for displaying winner
            std::cout << "we have a winner! " << winner << "\n";
            if(winner == 1) instructions.setString("You lost. Try again later.");
            else if(winner == -1) instructions.setString("You won! Good game.");
            else instructions.setString("It was a tie. Let's play again later.");
            sleep(1);
            exitScreen();
        }
    }
}

/**
 * @brief Draws the gameboard (broken into boardBackground and boardHoles) 
 *        and the cursor on the window.
 * 
 */
void App::drawGameBoard()
{
    window.draw(boardBackground);
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
            window.draw(boardHoles[i][j]);

    window.draw(cursor);
}

/**
 * @brief Provides a screen to show when exiting the game after a win
 *        or a draw. Allows exit after key pressed or exit button clicked.
 * 
 */
void App::exitScreen()
{
    sf::Vector2f backgroundPos = background.getPosition();
    instructions.setPosition(sf::Vector2f(backgroundPos.x-150.f, backgroundPos.y));
    instructions.setStyle(sf::Text::Bold);
    instructions.setCharacterSize(24);

    std::cout << "Thanks for playing!\n";
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        drawGameBoard();
        window.draw(background);
        window.draw(instructions);
        window.display();
    }
}

/**
 * @brief Moves the cursor left or right on the gameboard based on the key pressed.
 *        Moves the cursor a set amount to line up with the board holes.
 * 
 * @param direction sf::Keyboard::Key that was pressed, defaults to Unknown key
 */
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
}

/**
 * @brief Updates the board holes to the right color based
 *        on whose token is there. Computer is black, player
 *        is red.
 * 
 */
void App::updateGameBoard()
{
    for(int i=0; i<6; i++)
        for(int j=0; j<7; j++)
        {
            if(gameBoard.getBoard()[i][j] == 1)
                boardHoles[i][j].setFillColor(sf::Color::Black);
            else if(gameBoard.getBoard()[i][j] == -1)
                boardHoles[i][j].setFillColor(sf::Color::Red);
        }
}

/**
 * @brief Updates the cursor to match the color of whose
 *        turn it is to place a token.
 * 
 */
void App::updateCursor()
{
    if(whoStarts == 1)
        cursor.setFillColor(sf::Color::Black);
    else if(whoStarts == -1)
        cursor.setFillColor(sf::Color::Red);
}
