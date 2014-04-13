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

	// calculate possible directions that we can travel
	BOOL northWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, NORTH);
	BOOL eastWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, WEST);
	int numFree = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	Direction toGo;

	// if there is only one free, find that one
	if (numFree == 1) {
		if (!northWall) {
			toGo = NORTH;
		}
		else if(!eastWall) {
			toGo = EAST;
		}
		else if (!southWall) {
			toGo = SOUTH;
		}
		else {
			toGo = WEST;
		}

		if (toGo == mazemap_rotation_to_direction(curDirection, BACKWARDS)) {
			returning = TRUE;
		}
	}

	// check for returning case
	if (returning) {
		printf("returning\n");

		// if the current node hasn't been fully explored, start exploring it
		if (exploreHistory[yPos][xPos] != SEARCH_EXPLORED) {
			returning = FALSE;

			// increment the num explored nodes counter
			exploreHistory[yPos][xPos]++;
		}
		// otherwise, return the last direction on the stack
		else {
			return previousTravel[previousTravelPos--];
		}
	}

	// if there is more than one free, explore the next one that hasn't been
	else {
		Direction directionArray[] = {NORTH, EAST, SOUTH, WEST};
		BOOL wallArray[] = {northWall, eastWall, southWall, westWall};

		int numTimes = 0;
		for (int n = 0; n < 4; n++) {
			if (numTimes == exploreHistory[yPos][xPos]) {
				toGo = directionArray[n];
				break;
			}

			if (!wallArray[n]) {
				numTimes++;
			}
		}
	}

	// save the prevous travel on the stack
	previousTravel[++previousTravelPos] = toGo;

	return toGo;
}

#endif
