#ifndef EXPLORE_C
#define EXPLORE_C

#include <stdio.h>

#include "Explore.h"

MazeArray exploreHistory;		// keeps track of whether or not robot was there previously
BOOL returning = FALSE;			// returning state means robot is going back to previous source

Direction previousTravel[512];	// stack of previous turn directions
int previousTravelPos = -1;		// stack pointer

void explore_init()
{
	printf("initializing maglo_explore\n");

	// zero out the search array
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for(int col = 0; col < MAZE_HEIGHT; col++) {
			exploreHistory[row][col] = FALSE;
		}
	}
}

Direction explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory)
{
	// stack up positions that have multiple options to go
	// pop off only if we have traversed all locations.
	// When we hit a dead end, find shortest path to the
	// top location on the stack.  This should be the closest
	// branch location to our current position.

	// mark current location as explored
	exploreHistory[yPos][xPos] = TRUE;

	// check for returning case
	if (returning) {
		return_code:
		printf("returning\n");

		if (previousTravelPos == -1) {
			returning = FALSE;
		}
		else {
			// get the opposite direction that was pushed on the stack
			Direction prevDir = previousTravel[previousTravelPos--];
			Direction returnDirection = rotation_to_direction(prevDir, BACKWARDS);
			printf("returnDirection: %i\n", returnDirection);

			returning = FALSE;

			return returnDirection;
		}
	}

	// calculate possible directions that we can travel
	BOOL northWall = mm_is_wall(mazeMap, xPos, yPos, NORTH);
	BOOL eastWall = mm_is_wall(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mm_is_wall(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mm_is_wall(mazeMap, xPos, yPos, WEST);
	int numFree = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	Direction toGo;

	// if there is only one way to go, return
	if (numFree == 1) {
		returning = TRUE;
		goto return_code;
	}

	int numSearched = 0;
	if (!northWall && yPos < (MAZE_HEIGHT-1)) {
		if (exploreHistory[yPos + 1][xPos]) {
			numSearched++;
		}
		else {
			toGo = NORTH;
		}
	}
	if (!eastWall && xPos < (MAZE_WIDTH-1)) {
		if (exploreHistory[yPos][xPos + 1]) {
			numSearched++;
		}
		else {
			toGo = EAST;
		}
	}
	if (!southWall && yPos > 0) {
		if (exploreHistory[yPos - 1][xPos]) {
			numSearched++;
		}
		else {
			toGo = SOUTH;
		}
	}
	if (!westWall && xPos > 0) {
		if (exploreHistory[yPos][xPos - 1]) {
			numSearched++;
		}
		else {
			toGo = WEST;
		}
	}

	// return if there is nowhere else to go
	if (numSearched == numFree) {
		returning = TRUE;
		goto return_code;
	}

	// save the prevous travel on the stack
	previousTravel[++previousTravelPos] = toGo;

	printf("numSearched: %i\t", numSearched);
	printf("toGo: %i\n", toGo);
	return toGo;
}

#endif
