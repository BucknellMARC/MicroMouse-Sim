#ifndef SEARCH_H
#define SEARCH_H

#include "FloodFill.h"

typedef struct {
	int x;
	int y;
} MazePoint;

#define SEARCH_EXPLORED	4

// functions
void explore_init();
Direction explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory);

#endif
