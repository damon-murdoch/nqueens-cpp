#ifndef __SOLVE__HPP
#define __SOLVE__HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "board.hpp"

// bestFirstSearch(board: *boardPtr, range: int): int
int bestFirstSearch(Board * boardPtr, int range, int escape);

// simulatedAnnealing(board: *boardPtr, range: int): int
int simulatedAnnealing(Board * boardPtr, int range, double temp, double cool);

// geneticAlgorithm(board: *boardPtr, range: int): int
int geneticAlgorithm(Board * boardPtr, int range, int population, int generations);

#endif //__SOLVE__HPP