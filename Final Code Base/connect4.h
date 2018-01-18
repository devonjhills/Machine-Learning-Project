// Connect4.h
#ifndef Connect4_H
#define Connect4_H

#include <iostream>
#include <stdlib.h>
#include "engine.h"
#include "matrix.h"

class Connect4
{
private:
    int board[30][30];      // board[x][y]
    double myArray[42];        // array to pass to MATLAB
    bool droppieces;        // connect4 style pieces drop
    int xMax;               // max horizontal board size
    int yMax;               // max vertical board size
    int rowSize;            // need in a row to win
    int player;             // current player
    int totalTurns;         // how many turns so far?
    int maxTurns;           // full board
    int numberPlayers;      // 1 to 20
    bool playerType[9];     // true = human, false = comp

    int whoWon;

public:
    Connect4();

    void welcome();         // welcome screen

    void printTurn();       // whos turn?
    bool playerHuman();     // is player human?

    void humanMove();       // human controls
    void computerMove();    // computer strategy

    void drawBoard();       // display board

    bool winner();          // is there a winner?
    bool fullBoard();       // is the board full?

    void nextTurn();        // switch turn
    void setPlayerStart();

    void placePieces(int x, int y);     // move peices
    void announceWinner(int winner);    // winner!!

    void setWinner(int winner);
    int getWinner();

    int decide_move(double board_arr[]);

};

#endif // Connect4_H
