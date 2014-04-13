#ifndef SEARCH_C
#define SEARCH_C

#include <stdio.h>

#include "Search.h"

MazeArray exploreHistory;		// keeps track of whether or not robot was there previously
BOOL returning = FALSE;			// returning state means robot is going back to previous source

Direction previousTravel[512];	// stack of previous turn directions
int previousTravelPos = -1;		// stack pointer

void malgo_explore_init()
{
	printf("initializing maglo_explore\n");

	// zero out the search array
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for(int col = 0; col < MAZE_HEIGHT; col++) {
			exploreHistory[row][col] = 0;
		}
	}
}

Direction malgo_explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory)
{
	// stack up positions that have multiple options to go
	// pop off only if we have traversed all locations.
	// When we hit a dead end, find shortest path to the
	// top location on the stack.  This should be the closest
	// branch location to our current position.

	// check for returning case
	if (returning) {
		return_code:
		printf("returning\n");

		// if the current node hasn't been fully explored, start exploring it
		if (exploreHistory[yPos][xPos] != SEARCH_EXPLORED) {
			returning = FALSE;

			// increment the num explored nodes counter
			exploreHistory[yPos][xPos]++;
		}
		// otherwise, go backwards
		else {
			// get the opposite direction that was pushed on the stack
			Direction prevDir = previousTravel[previousTravelPos--];
			Direction returnDirection = mazemap_rotation_to_direction(prevDir, BACKWARDS);
			printf("returnDirection: %i\n", returnDirection);

			return returnDirection;
		}
	}

	// calculate possible directions that we can travel
	BOOL northWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, NORTH);
	BOOL eastWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, WEST);
	int numFree = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	Direction toGo;

	// if there is only one way to go, return
	if (numFree == 1) {
		returning = TRUE;
		goto return_code;
	}

	// if there is more than one free, explore the next one that hasn't been
	Direction directionArray[] = {NORTH, EAST, SOUTH, WEST};
	BOOL wallArray[] = {northWall, eastWall, southWall, westWall};

	int numTimes = 0;
	int n;
	for (n = 0; n < 4; n++) {
		if (numTimes == exploreHistory[yPos][xPos]) {
			toGo = directionArray[n];
			break;
		}

		if (!wallArray[n]) {
			numTimes++;
		}
	}

	// return if there is nowhere else to go
	if (n == 4) {
		returning = TRUE;
		goto return_code;
	}

	// save the prevous travel on the stack
	previousTravel[++previousTravelPos] = toGo;

	printf("numTimes: %i\t", numTimes);
	printf("toGo: %i\n", toGo);
	return toGo;
}

#endif
