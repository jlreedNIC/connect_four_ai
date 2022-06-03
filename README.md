# connect_four_ai
This was an assignment for CS 470, Artificial Intelligence, taken at the University of Idaho. The assignment requirements are listed below. The goal was to create a program to be able to play a game of Connect Four against a computer. This was coded using SFML for the graphics library.

## Assignment Requirements
Goal: Write a program to play Connect Four against a human opponent.

Connect Four is played on a vertical board with 7 columns each 6 positions high . Players alternate dropping different colored pieces into one of the 7 columns. Once a column is filled (i.e. six pieces have been dropped into it) that column is no longer a legal move. The goal is to get four pieces in a row: vertically, horizontally, or diagonally. It is possible for the game to be a tie, if the board is filled without anyone connecting four pieces. This is a relatively easy game for computers because of the low branching factor. There are lots of on-line versions (e.g. https://www.mathsisfun.com/games/connect4.html) if you want to play.

Requirements: The program must use a minimax search algorithm (it can be coded as negamax). The user must be able to determine which side goes first. The program must display the board after each move. (This can be a simple text based display.) The program should not take more than about 10 seconds to make a move.

Algorithms: Your program must use, at least, minimax search. You will need to write an evaluation heuristic because searching the entire game tree is not feasible. If your minimax/negamax algorithm is working properly the program should always block a potential win by the opponent (if there are three opponent pieces in a row the computer places a piece to block the win) and always makes a winning move if one is available. Note: if there are two possible paths to a sure victory the program may take the longer one.

## Status
Finished. Only compiled for Linux machines.

## To Run on Linux
- Install SFML libraries.
- Download code
- Run 'make test' in the folder you downloaded to
- Play