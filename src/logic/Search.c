#ifndef SEARCH_C
#define SEARCH_C

#include "Search.h"

#define SEARCH_STACK_SIZE 128
MazeArray searchArray;
MazePoint searchStack[SEARCH_STACK_SIZE];
int searchStackPos = -1;

Direction malgo_explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory)
{
	Direction outDir;

	// stack up positions that have multiple options to go
	// pop off only if we have traversed all locations.
	// When we hit a dead end, find shortest path to the
	// top location on the stack.  This should be the closest
	// branch location to our current position.

	return NORTH; 
}


#endif
