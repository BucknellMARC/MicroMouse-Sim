#ifndef EXPLORE_C
#define EXPLORE_C

#include <stdio.h>

#include "Explore.h"

Direction explore_return();		// pops previousTravel and returns the oppposite direction

MazeArray exploreHistory;		// keeps track of whether or not robot was there previously
BOOL returning = FALSE;			// returning state means robot is going back to previous source

Direction previousTravel[512];	// stack of previous turn directions
int previousTravelPos = -1;		// stack pointer

void explore_init()
{
	// zero out the search array
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for(int col = 0; col < MAZE_HEIGHT; col++) {
			exploreHistory[row][col] = FALSE;
		}
	}
}

Direction explore_suggest(Point pos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory)
{
	// stack up positions that have multiple options to go
	// pop off only if we have traversed all locations.
	// When we hit a dead end, pop return values off stack
	// until we reach a node that has unexplored adjacent nodes

	// mark current location as explored
	exploreHistory[pos.y][pos.x] = TRUE;

	// check for returning case
	if (returning) {
		return explore_return();
	}

	// calculate possible directions that we can travel
	BOOL northWall = mm_is_wall(mazeMap, pos, NORTH);
	BOOL eastWall = mm_is_wall(mazeMap, pos, EAST);
	BOOL southWall = mm_is_wall(mazeMap, pos, SOUTH);
	BOOL westWall = mm_is_wall(mazeMap, pos, WEST);
	int numFree = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	Direction toGo;

	// if there is only one way to go, return
	if (numFree == 1) {
		returning = TRUE;
		return explore_return();
	}

	int numSearched = 0;
	if (!northWall && pos.y < (MAZE_HEIGHT-1)) {
		if (exploreHistory[pos.y + 1][pos.x]) {
			numSearched++;
		}
		else {
			toGo = NORTH;
		}
	}
	if (!eastWall && pos.x < (MAZE_WIDTH-1)) {
		if (exploreHistory[pos.y][pos.x + 1]) {
			numSearched++;
		}
		else {
			toGo = EAST;
		}
	}
	if (!southWall && pos.y > 0) {
		if (exploreHistory[pos.y - 1][pos.x]) {
			numSearched++;
		}
		else {
			toGo = SOUTH;
		}
	}
	if (!westWall && pos.x > 0) {
		if (exploreHistory[pos.y][pos.x - 1]) {
			numSearched++;
		}
		else {
			toGo = WEST;
		}
	}

	// return if there is nowhere else to go
	if (numSearched == numFree) {
		returning = TRUE;
		return explore_return();
	}

	// save the prevous travel on the stack
	previousTravel[++previousTravelPos] = toGo;
	return toGo;
}

Direction explore_return()
{
	if (previousTravelPos == -1) {
		returning = FALSE;
	}
	else {
		// get the opposite direction that was pushed on the stack
		Direction prevDir = previousTravel[previousTravelPos--];
		Direction returnDirection = rotation_to_direction(prevDir, BACKWARDS);

		returning = FALSE;

		return returnDirection;
	}
}

#endif
