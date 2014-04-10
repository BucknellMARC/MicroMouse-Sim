#ifndef SEARCH_H
#define SEARCH_H

#include "FloodFill.h"

typedef struct {
	int x;
	int y;
} MazePoint;

// functions
Direction malgo_explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory);

#endif
