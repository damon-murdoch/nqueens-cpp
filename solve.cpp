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
    for(int i = 1; i <= range; i++)
    {
      // If space right is on the grid
      if((q->x + i) < boardPtr->getSize())
      {
        // If space right is not occupied, add to list
        Point pRight = Point::Point(q->x + i, q->y);
        if (!boardPtr->at(&pRight)){moves.push_back(pRight);}
      }
      // If space left is on the grid
      if((q->x - i) >= 0)
      {
        // If space left is not occupied, add to list
        Point pLeft = Point::Point(q->x - i, q->y);
        if (!boardPtr->at(&pLeft)){moves.push_back(pLeft);}
      }
      // If space down is on the grid
      if((q->y + i) < boardPtr->getSize())
      {
        // If space down is not occupied, add to list
        Point pDown = Point::Point(q->x, q->y + i);
        if (!boardPtr->at(&pDown)){moves.push_back(pDown);}
      }
      // If space up is on the grid
      if((q->y - i) >= 0)
      {
        // If space up is not occupied, add to list
        Point pUp = Point::Point(q->x, q->y - i);
        if (!boardPtr->at(&pUp)){moves.push_back(pUp);}
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

  // While the temperature is greater than 1
  while (curTemp > 0.001)
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
      // If space right is on the grid
      if((q->x + i) < boardPtr->getSize())
      {
        // If space right is not occupied, add to list
        Point pRight = Point::Point(q->x + i, q->y);
        if (!boardPtr->at(&pRight)){moves.push_back(pRight);}
      }
      // If space left is on the grid
      if((q->x - i) >= 0)
      {
        // If space left is not occupied, add to list
        Point pLeft = Point::Point(q->x - i, q->y);
        if (!boardPtr->at(&pLeft)){moves.push_back(pLeft);}
      }
      // If space down is on the grid
      if((q->y + i) < boardPtr->getSize())
      {
        // If space down is not occupied, add to list
        Point pDown = Point::Point(q->x, q->y + i);
        if (!boardPtr->at(&pDown)){moves.push_back(pDown);}
      }
      // If space up is on the grid
      if((q->y - i) >= 0)
      {
        // If space up is not occupied, add to list
        Point pUp = Point::Point(q->x, q->y - i);
        if (!boardPtr->at(&pUp)){moves.push_back(pUp);}
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
    vector<Point>::iterator it = moves.begin();

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

  // If the heuristic is greater than zero, run
  // a heuristic search to finish up the search
  if (h > 0) bestFirstSearch(boardPtr, range, temp);

  // Return the heuristic
  return h;
}

// geneticAlgorithm(board: *boardPtr, range: int): int
int geneticAlgorithm(Board * boardPtr, int range, int population, int generations)
{
  // Get the current collisions in the board
  int h = boardPtr->getHeuristic();

  // Generation Counter
  int g = 0;

  // Size counter
  int size = boardPtr->getSize();

  // Create empty board array
  vector<Board> boards;

  // Loop over the population count
  while(boards.size() < population)
  {
    // Add a clone of the current board to the list
    boards.push_back(Board::Board(boardPtr));
  }

  // While the heuristic cost is greater than zero, AND
  // we have not passed the generational limit (if it exists)
  while(h > 0 && (!generations || (g < generations)))
  {
    // Half of the population is kept each generation 
    // and half of the population is thrown away

    // Loop over all of the elements in the population
    for(int i=0; i<population; i++)
    {
      // Add a modified copy of the board at the 
      // current index to the back of the vector
      boards.push_back(Board::Board(&(boards[i])));

      // Get the partner index
      // Partner is the last element of the array
      int p = population - i - 1;

      for(int j=0; j<range; j++)
      {
        // Crossover 'j' from a 'j' in the partner
        Point point = Point::Point(boards.at(p).queens.at(j));

        // If the select point is not a duplicate, accept the crossover
        if (!(boards.back().at(&point)))
        {
          // Replace the existing queen with the crossover queen
          boards.back().queens.at(j) = point;
        }
      }

      // Perform a heuristic search on the board state
      bestFirstSearch(&(boards.back()), size, size);
      
      // Break out of the loop if we have found a solution
      if (boards.back().getHeuristic() == 0) break;
    }

    // Sort the vector using the heuristic
    sort(boards.begin(), boards.end(), compare_h);

    // Reset the size of the vector to the population size
    boards.resize(population);

    // Update the current best heuristic with the first (best) element
    h = boards.front().getHeuristic();

    // Increment the generations counter
    g++;
  }

  // Update the starting board with the best result
  *boardPtr = Board::Board(&(boards.front()));

  // Return the heuristic
  return h;
}

#endif //__SOLVE__CPP