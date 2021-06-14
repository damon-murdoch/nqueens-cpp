#ifndef __SOLVE__CPP
#define __SOLVE__CPP

#include "solve.hpp"

using namespace std;

// simulatedAnnealing(board: *Board, range: int): int
int bestFirstSearch(Board * boardPtr, int range, int escape)
{
  // Get the current collisions in the board
  int h = boardPtr->getHeuristic();

  // False Moves (No improvement, or no better moves)
  int f = 0;

  // While we are not in a local minimum
  // AND we have not reached a heuristic of 0
  while(h > 0)
  {
    // If the escape range is set
    // and the false moves counter
    // is greater than the limit
    if (escape > 0 && f > escape)
    {
      // Break out of the loop
      break;
    }

    // Get a pointer to a random queen
    Point * q = &(boardPtr->queens.at(rand() % boardPtr->getSize()));

    // Dereference the values of the random queen (as a backup)
    // If no better result is found, this may need to be restored
    Point backup = Point::Point(*q);

    // Get all of the possible movements of the queen
    vector<Point> moves;

    // Loop over the possible movements
    for(int i=1; i <= range; i++)
    {
      if((q->x + i) < boardPtr->getSize())
      {
        moves.push_back(Point::Point(q->x + i, q->y));
      }
      if((q->x - i) >= 0)
      {
        moves.push_back(Point::Point(q->x - i, q->y));
      }
      if((q->y + i) < boardPtr->getSize())
      {
        moves.push_back(Point::Point(q->x, q->y + i));
      }
      if((q->y - i) >= 0)
      {
        moves.push_back(Point::Point(q->x, q->y - i));
      }
    }

    // Current best 'h' value is the current 'h' value
    int best = h;

    // Current test 'h' value
    int now;

    // Index of the current best, -1 == no better found
    int index = -1;

    // Shuffle the options vector 
    // (to ensure that same option is not always picked)
    random_shuffle(moves.begin(), moves.end());

    // Create an iterator for the moves list
    std::vector<Point>::iterator it = moves.begin();

    // Loop over the iterator
    for(; it != moves.end(); ++it)
    {
      // Replace the board values with the test value
      q->x = it->x;
      q->y = it->y;

      // Get the board heuristic with the new position
      now = boardPtr->getHeuristic();

      // If the current value is better
      // or same as the previous best
      if (now <= best)
      {
        // Save the new one

        // h value
        best = now; 

        // index
        index = it - moves.begin(); 
      }
    }

    // If the index has not been changed
    if (index == -1)
    {
      // Set the current position back to original
      q->x = backup.x; 
      q->y = backup.y;
    }
    else
    {
      // Set the current position to the best result
      q->x = moves.at(index).x; 
      q->y = moves.at(index).y;
    }

    // If the current 'h' is less than the previous
    if (best < h)
    {
      // Position has been changed, set f to 0
      // We are not stuck so we can keep searching
      f = 0;
    }

    // Update the current heuristic
    h = best;

    // Increment the false moves counter
    f++;
  }

  // Return the heuristic value
  return h;
}

// simulatedAnnealing(board: *Board, range: int): int
int simulatedAnnealing(Board * boardPtr, int range, double temp, double cool)
{
  // Get the current collisions in the board
  int h = boardPtr->getHeuristic();

  // Current temperature
  double curTemp = temp;

  // While the temperature is greater than 0
  while (curTemp > 0.00001)
  {
    // Get a pointer to a random queen
    Point * q = &(boardPtr->queens.at(rand() % boardPtr->getSize()));

    // Dereference the values of the random queen (as a backup)
    // If no better result is found, this may need to be restored
    Point backup = Point::Point(*q);

    // Get all of the possible movements of the queen
    vector<Point> moves;

    // Loop over the possible movements
    for(int i = 1; i <= range; i++)
    {
      if((q->x + i) < boardPtr->getSize())
      {
        moves.push_back(Point::Point(q->x + i, q->y));
      }
      if((q->x - i) >= 0)
      {
        moves.push_back(Point::Point(q->x - i, q->y));
      }
      if((q->y + i) < boardPtr->getSize())
      {
        moves.push_back(Point::Point(q->x, q->y + i));
      }
      if((q->y - i) >= 0)
      {
        moves.push_back(Point::Point(q->x, q->y - i));
      }
    }

    // Current best 'h' value is the current 'h' value
    int best = h;

    // Current test 'h' value
    int now;

    // Index of the current best, -1 == no better found
    int index = -1;

    // Shuffle the options vector 
    // (to ensure that same option is not always picked)
    random_shuffle(moves.begin(), moves.end());

    // Create an iterator for the moves list
    std::vector<Point>::iterator it = moves.begin();

    // Loop over the iterator
    for(; it != moves.end(); ++it)
    {
      // Replace the board values with the test value
      q->x = it->x;
      q->y = it->y;

      // Get the board heuristic with the new position
      now = boardPtr->getHeuristic();

      // If the current value is better than the previous best OR it is greater 
      // and passes the acceptance function
      if (now < best || exp( - (now - h) / curTemp) > (double)rand() / RAND_MAX)
      {
        // h value
        best = now; 

        // index
        index = it - moves.begin(); 
      }

      // cout << exp( - (now - h) / curTemp) << endl;
    }

    // If the index has not been changed
    if (index == -1)
    {
      // Set the current position back to original
      q->x = backup.x; 
      q->y = backup.y;
    }
    else
    {
      // Set the current position to the best result
      q->x = moves.at(index).x; 
      q->y = moves.at(index).y;
    }

    // Update the current heuristic
    h = best;

    // Reduce the temperature by the cooling factor
    curTemp *= cool;
  }

  // Return the heuristic
  return h;
}

#endif //__SOLVE__CPP