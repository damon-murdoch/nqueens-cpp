#ifndef __SOLVE__HPP
#define __SOLVE__HPP

#include <iostream>

#include "board.hpp"

// simulatedAnnealing(board: *Board, range: int): int
int bestFirstSearch(Board * boardPtr, int range);

// simulatedAnnealing(board: *Board, range: int): int
int simulatedAnnealing(Board * boardPtr, int range);

#endif //__SOLVE__HPP