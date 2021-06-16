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
  Point();
};

class Board 
{
  public:
  std::vector<Point>queens;
  Board();
  Board(int size);
  Board(Board * other);
  int getHeuristic();
  int getSize();
  bool at(Point * p);
  bool at(int x, int y);
  void print();
};

bool compare(Point * a, Point * b);
bool compare_h(Board a, Board b);

#endif //__BOARD__HPP