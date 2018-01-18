// main.cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "connect4.h"

using namespace std;

  // insert decide_move function here
  Engine *ep = NULL;

int main(int argc, char* argv[])
{

  // INIT MATLAB
    // insert decide_move function here
  if (!(ep = engOpen(NULL))) {
    fprintf(stderr, "\nCan't start MATLAB engine\n");
    exit(-1);
  }
   engEvalString(ep, "cd('/Users/doug/School/Junior/Spring/Machine Learning/project/quasi-final-copy');");

  
    //Connect4 Game;

    int p1win = 0;
    int p2win = 0;

    istringstream iss(argv[1]);
    int gamecount;
    iss >> gamecount;

    //Game.welcome();
    //Game.drawBoard();

    srand (time(0));

    for(int i = 0; i < gamecount; i++) {
      cout << "Playing game " << (i + 1) << ".\n";
        Connect4 Game;
        Game.setPlayerStart(); // random player starts game
        Game.drawBoard();
        do
        {

            //Game.printTurn();
            if (Game.playerHuman()) // human turn?
                Game.humanMove();
            else
                Game.computerMove();

            Game.drawBoard();
            Game.nextTurn();

        }
        while (!Game.winner() && !Game.fullBoard());

        if(Game.getWinner() == 1) {
            p1win++;
        } else if(Game.getWinner() == 2) {
            p2win++;
        }
    }

    cout << "Learning Machine win count: " << p1win << endl <<
            "Random Computer  win count: " << p2win << endl;


    return 0;
}
