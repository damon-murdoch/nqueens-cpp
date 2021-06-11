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

    bestFirstSearch(board, board->getSize(),pow(10, board->getSize()));

    cout << "Final H: " << board->getHeuristic() << endl;

    board->print();
  }
  else
  {
    // Demo: Test all from 4 -> 32 100 times each, and get an accuracy %

    int start = 4;
    int end = 32;

    // Number of repetitions before giving up on a state
    int fail = pow(2, 19);

    // Run 100 tests for each size
    int tests = 100; 

    int overall_acc = 0;
    int overall_avg = 0;
    int overall_time = 0;
    int overall_tests = (end - start + 1) * tests;
   
    // Size Parameter
    for(int i = start; i <= end; i++)
    {
      // Increment every time we find '0'
      int success = 0;

      // Average final board state
      int avg = 0;

      // Average time taken (microseconds)
      int time = 0;

      // Number of tests
      for(int j = 0; j < tests; j++)
      {
        // Record starting clock time
        auto start = chrono::high_resolution_clock::now();

        // Create a new board of the specified size
        Board * board = new Board(i);

        // Use the best first search algorithm to solve the board
        int result = bestFirstSearch(board, board->getSize(),1000000);

        // Record ending clock time
        auto end = chrono::high_resolution_clock::now();

        // Difference between start time and end time
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        // Add the number of milliseconds to the total time
        time += duration.count();

        // cout << duration.count() << endl;

        // If result is 0, increment successes
        if (result == 0) success++;

        // Add result to the average
        avg += result;
      }

      // Add the current sucess count
      // and current average remainder 
      // to the overall counter

      overall_acc += success;
      overall_avg += avg;
      overall_time += time;

      // Write the results to the output stream

      cout << "Accuracy for " << i << ": " << (((float)success / (float)tests) * 100); 
      cout << "% (" << success << "/" << tests << ")" << ", Avg. Result: "; 
      cout << ((float)avg / (float)tests) << ", Avg. Time: ";
      cout << ((float)time / (float)tests) << "ms" << endl;
    }

    cout << "Overall accuracy: " << (((float)overall_acc / (float)overall_tests) * 100);
    cout << "% (" << overall_acc << "/" << overall_tests << ")" << ", Avg. Result: ";
    cout << ((float)overall_avg / (float)overall_tests) << ", Avg. Time: ";
      cout << ((float)overall_time / (float)overall_tests) << "ms" << endl;
  }

  return 0;
}

#endif // __MAIN__CPP