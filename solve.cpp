#ifndef __SOLVE__CPP
#define __SOLVE__CPP

#include "solve.hpp"

using namespace std;

// simulatedAnnealing(board: *Board, range: int): int
int bestFirstSearch(Board * boardPtr, int range)
{
  // Get the current collisions in the board
  int h = boardPtr->getHeuristic();

  cout << "Collisions: " << h << endl;

  return h;
}

// simulatedAnnealing(board: *Board, range: int): int
int simulatedAnnealing(Board * boardPtr, int range)
{
  // Get the current collisions in the board
  int h = boardPtr->getHeuristic();

  return h;
}

#endif //__SOLVE__CPP