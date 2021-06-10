#ifndef __MAIN__CPP
#define __MAIN__CPP

#include "main.hpp"

using namespace std;

int main(int argc, char ** argv)
{
  // Seed the random number generator
  srand(time(NULL));

  // If a size argument is provided, use it
  // Otherwise, use the default size of 4
  
  int n = argc > 1 ? atoi(argv[1]): 8;

  // Create a new board of the specified size
  Board * board = new Board(n);

  board->print();

  bestFirstSearch(board, 1);

  board->print();

  return 0;
}

#endif // __MAIN__CPP