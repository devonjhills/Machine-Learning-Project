// Connect4.cpp
// #define DRAW_TURNS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect4.h"

extern Engine *ep;

Connect4::Connect4()
{
    player = 1;         // who starts?

    xMax = 7;          // x size of gameboard
    yMax = 6;          // y size of gameboard
    rowSize = 4;        // how many in a row to win?

    droppieces = true;     // 1 = pieces drop, 0 = stay

    // new player setup
    numberPlayers = 2;      // how many players?

    playerType[1] = 1;      // smart AI
    playerType[2] = 0;      // player # 2 is comp (0)

    totalTurns = 0;         // used for boardFull()
    maxTurns = xMax * yMax; // (total board spaces)

    // format game board
    for (int y = 0; y < yMax; y++)
        for (int x = 0; x < xMax; x++)
            board[x][y] = 0;

}

void Connect4::welcome()
{
    std::cout << "Connect 4 Game" << std::endl;
}

void Connect4::drawBoard()
{
  #ifdef DRAW_TURNS
    std::cout << std::endl;
    for (int label = 1; label <= 7; label++) {
        std::cout << " " << label << "  ";
    }
    std::cout << std::endl;
    for (int y = 0; y < yMax; y++)
    {

        // draw game board and pieces
        for (int x = 0; x < xMax; x++)
        {
            // no piece then just draw space
            if (!board[x][y])
                std::cout << "   ";
            else
                std::cout << " " << board[x][y] << " ";

            // draw seperator if not end
            if (x < xMax - 1)
                std::cout << "│";
        }

        std::cout << std::endl;

        // draw seperator line between board
        for (int z = 0; z < xMax; z++)
        {
            // draw seperator if not end
            if (y < yMax - 1)
            {
                std::cout << "───";
                // draw connection if not end
                if (z < xMax - 1)
                    std::cout << "┼";
            }
        }

        std::cout << std::endl;
	}


    #endif
}

void Connect4::printTurn()
{
    std::cout << "Player " << player << "'s turn.\n";
}

void Connect4::nextTurn()
{
    totalTurns++;

    // start again at first player
    if (++player > numberPlayers)
        player = 1;
}

bool Connect4::playerHuman()
{
    return playerType[player];
}


int Connect4::decide_move(double board_arr[]) {
  
  // Send the board to Matlab
  mxArray * board = NULL;
  board = mxCreateDoubleMatrix(1, 42, mxREAL);
  memcpy((void *)mxGetPr(board), (void *)board_arr, 42 * sizeof(double));
  if ((engPutVariable(ep, "board", board)) == 1) {
    std::cout << "Failed to send the board to Matlab\n";
  }

  // Run the Matlab code to get a prediction
  engEvalString(ep, "move = decide_move(board);");

  // Retrieve the result
  double move = ((double *)mxGetData(engGetVariable(ep, "move")))[0];
  
  mxDestroyArray(board);

  return (int)move;
}


void Connect4::humanMove()
{
  int moveX, moveY = 0;
  int q = 0;

  // Get the state of the board as an array
  for (int x = 0; x < xMax; x++) {
    for (int y = 5; y >= 0; y--) {
      myArray[q] = (double)board[x][y];
      q++;
    }
  }

  // Decide the move
  moveX = decide_move(myArray);
  moveX--;

  // Finish
  if (board[moveX][moveY]) {
    std::cout << "ERROR: The machine has attempted an invalid move to slot " << (moveX + 1)<< "!\n";
    exit(1);
  }
  placePieces(moveX, moveY);
}

void Connect4::setPlayerStart() {
    player = (rand() % 2) + 1;
}

void Connect4::computerMove()
{

    int moveX, moveY;
    
    do
    {
     moveX  = rand() % xMax; // pick a random spot
     //moveY  = rand() % yMax; // pick a random spot
      moveY = 0;
    }
    while (board[moveX][moveY]);    // loop if taken

    placePieces(moveX, moveY);

}

void Connect4::placePieces(int x, int y)
{
    if (droppieces)
    {
        while (y++ < yMax - 1 && !board[x][y]){}
        y--;  // the last place was taken so go back one
    }

    board[x][y] = player;

}

bool Connect4::winner()
{
    int matchcount = 0;
    int lastmatch = 0;


    // check x row
    for (int y = 0; y < yMax; y++)
        for (int x = 0; x + rowSize - 1 < xMax; x++)
        {
            matchcount = 0;
            lastmatch = board[x][y];

            // check through columns
            for (int z = 0; z < rowSize; z++)
                if (board[x+z][y] && board[x+z][y] ==
                    lastmatch && ++matchcount == rowSize)
                {
                    announceWinner(lastmatch);
                    return true;
                }
        }

    // check y row
    for (int y = 0; y + rowSize - 1 < yMax; y++)
        for (int x = 0; x < xMax; x++)
        {
            matchcount = 0;
            lastmatch = board[x][y];

            // check through rows
            for (int z = 0; z < rowSize; z++)
                if (board[x][y+z] && board[x][y+z] ==
                    lastmatch && ++matchcount == rowSize)
                {
                    announceWinner(lastmatch);
                    return true;
                }
        }

    // move through columns
    for (int y = 0; y + rowSize - 1 < yMax; y++)
        for (int x = 0; x < xMax; x++)
        {
            matchcount = 0;
            lastmatch = board[x][y];

            // check through rows
            for (int z = 0; z < rowSize; z++)
                if (board[x+z][y+z] && board[x+z][y+z] ==
                    lastmatch && ++matchcount == rowSize)
                {
                    announceWinner(lastmatch);
                    return true;
                }
    }


    // move through columns
    for (int y = 0; y + rowSize <= yMax; y++)
        for (int x = xMax - 1; x - rowSize + 1 >= 0; x--)
        {
            matchcount = 0;
            lastmatch = board[x][y];

            // check through rows
            for (int z = 0; z < rowSize; z++)
                if (board[x-z][y+z] && board[x-z][y+z] ==
                    lastmatch && ++matchcount == rowSize)
                {
                    announceWinner(lastmatch);
                    return true;
                }
    }

    return false;
}

void Connect4::announceWinner(int winner)
{
    if(winner == 1) {
        setWinner(1);
    } else if(winner == 2) {
        setWinner(2);
    }

    //std::cout << "\nPlayer " << winner << " wins!\n\n";
}

void Connect4::setWinner(int winner) {
    if(winner == 1) {
        whoWon = 1;
    } else {
        whoWon = 2;
    }
}

int Connect4::getWinner() {
    return whoWon;
}

bool Connect4::fullBoard()
{
    if (totalTurns == maxTurns)
    {
        //std::cout << "\nTie game!\n\n";
        return true;
    }

    return false;
}
