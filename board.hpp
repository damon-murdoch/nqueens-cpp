#ifndef __BOARD__HPP
#define __BOARD__HPP

#include <iostream>
#include <vector>

class Point
{
  public:
  int x;
  int y;
  Point(int x, int y);
};

class Board 
{
  public:
  std::vector<Point>queens;
  Board(int size);
  int getHeuristic();
  void print();
};

bool compare(Point * a, Point * b);

#endif //__BOARD__HPP