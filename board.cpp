#ifndef __BOARD__CPP
#define __BOARD__CPP

#include "board.hpp"

using namespace std;

bool compare(Point * a, Point * b)
{
  return (a -> x == b -> x) && (a -> y == b -> y);
}

Point::Point(int x, int y)
{
  this->x = x;
  this->y = y;
}

Board::Board(int size)
{
  // Vector of array points
  this->queens = vector::vector<Point>();

  // Repeat for 'size' times
  for(int i=0; i<size; i++)
  {
    // Add a random queen to the list 
    this->queens.push_back(Point::Point(rand() % size, rand() % size));
  }
}

int Board::getSize()
{
  // Return the size of the queens list
  return this->queens.size();
}

int Board::getHeuristic()
{
  // Check every queen against every other queen

  // Number of Collisions
  int h = 0;

  for(int i = 0; i<this->queens.size() - 1; i++)
  {
    for(int j = i + 1; j<this->queens.size(); j++)
    {
      // Do not check queen against itself
      //if (i == j) continue;

      // If the queens are overlapping
      if (compare(&(this->queens.at(i)),&(this->queens.at(j))))
      {
        // Increment the 'h' value
        // Want to increase by 99, because
        // Having two queens in the same spot is an 
        // impossible state and we want to avoid this 
        // at all costs!
        h += 99;
      }

      // If the queens 'x' location is the same
      else if (this->queens.at(i).x == this->queens.at(j).x)
      {
        // Increment the 'h' value
        h++;
      }

      // If the queens 'y' location is the same
      else if (this->queens.at(i).y == this->queens.at(j).y)
      {
        // Increment the 'h' value
        h++;
      }
      // If the queens are diagonal to each other

      // If the 'difference between the 'x' and 'y' is the same
      else if (abs(this->queens.at(i).y - this->queens.at(j).y) == 
        abs(this->queens.at(i).x - this->queens.at(j).x))
      {
        // Increment the 'h' value
        h++;
      }
    }
  }

  return h;
}

void Board::print()
{
  // Output map object, same length as queen count
  vector<vector<bool>> map(this->queens.size(),vector::vector<bool>(this->queens.size(), false));

  // Loop over the queens in the list
  for(int i=0; i<this->queens.size(); i++)
  {
    // Set the point on the map to true
    map.at(this->queens.at(i).y).at(this->queens.at(i).x) = true;
  }

  // Loop over the y axis
  for(int i=0; i<this->queens.size(); i++)
  {
    // Loop over the x axis
    for(int j=0; j<this->queens.size(); j++)
    {
      // Print a hashtag if this is a queen, blank space if it is not
      if (map.at(i).at(j) == true)
      {
        cout << "#";
      }
      else
      {
        cout << " ";
      }
    }
    // Print the newline
    cout << endl;
  }
}

#endif //__BOARD__CPP