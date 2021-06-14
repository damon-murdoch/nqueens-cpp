#ifndef __SOLVE__HPP
#define __SOLVE__HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "board.hpp"

// bestFirstSearch(board: *Board, range: int): int
int bestFirstSearch(Board * boardPtr, int range, int escape);

// simulatedAnnealing(board: *Board, range: int): int
int simulatedAnnealing(Board * boardPtr, int range, double temp, double cool);

// geneticAlgorithm(board: *Board, )
int geneticAlgorithm(): int

#endif //__SOLVE__HPP