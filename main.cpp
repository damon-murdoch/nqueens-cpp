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
  
  int n = argc > 1 ? atoi(argv[1]): -1;

  // Provided a size argument, single test
  if(n > 3)
  {
    // Create a new board of the specified size
    Board * board = new Board(n);

    cout << "Current H: " << board->getHeuristic() << endl;

    board->print();

    bestFirstSearch(board, board->getSize(),-1);

    cout << "Final H: " << board->getHeuristic() << endl;

    board->print();
  }
  else
  {
    // Demo: Test all from 4 -> 32 100 times each, and get an accuracy %

    int start = 4;
    int end = 32;

    // Number of repetitions before giving up on a state
    int fail = pow(2, 12);

    // Run 100 tests for each size
    int tests = 100; 

    // Size Parameter
    for(int i = start; i <= end; i++)
    {
      // Increment every time we find '0'
      int successBfs = 0;
      int successAnn = 0;

      // Average final board state
      int avgBfs = 0;
      int avgAnn = 0;

      // Average time taken (microseconds)
      int timeBfs = 0;
      int timeAnn = 0;

      // Number of tests
      for(int j = 0; j < tests; j++)
      {
        // Best First Search

        // Record starting clock time
        auto startBfs = chrono::high_resolution_clock::now();

        // Create a new board of the specified size
        Board * boardBfs = new Board(i);

        // Use the best first search algorithm to solve the board
        int resultBfs = bestFirstSearch(boardBfs, boardBfs->getSize(),fail);

        // Record ending clock time
        auto endBfs = chrono::high_resolution_clock::now();

        // Difference between start time and end time
        auto durationBfs = chrono::duration_cast<chrono::milliseconds>(endBfs - startBfs);

        // Add the best first search duration to the total annealing time
        timeBfs += durationBfs.count();

        // If result is 0, increment successes
        if (resultBfs == 0) successBfs++;
      }

      // Write the results to the output stream

      cout << "Best First Search (" << i << "): " << (((float)successBfs / (float)tests) * 100); 
      cout << "% (" << successBfs << "/" << tests << ")" << ", Avg. Result: "; 
      cout << ((float)avgBfs / (float)tests) << ", Avg. Time: ";
      cout << ((float)timeBfs / (float)tests) << "ms" << endl;

      // Number of tests
      for(int j = 0; j < tests; j++)
      {
        // Simulated Annealing

        // Record starting clock time
        auto startAnn = chrono::high_resolution_clock::now();

        // Create a new board of the specified size
        Board * boardAnn = new Board(i);

        // Use the best first search algorithm to solve the board
        int resultAnn = simulatedAnnealing(boardAnn, boardAnn->getSize(), 10.0, 0.99);

        // Record ending clock time
        auto endAnn = chrono::high_resolution_clock::now();

        // Difference between start time and end time
        auto durationAnn = chrono::duration_cast<chrono::milliseconds>(endAnn - startAnn);

        // Add the annealing duration to the total annealing time
        timeAnn += durationAnn.count();

        // If result is 0, increment successes
        if (resultAnn == 0) successAnn++;
      }

      // Write the results to the output stream

      cout << "Annealing Search (" << i << "): " << (((float)successAnn / (float)tests) * 100); 
      cout << "% (" << successAnn << "/" << tests << ")" << ", Avg. Result: "; 
      cout << ((float)avgAnn / (float)tests) << ", Avg. Time: ";
      cout << ((float)timeAnn / (float)tests) << "ms" << endl;
    }
  }

  return 0;
}

#endif // __MAIN__CPP