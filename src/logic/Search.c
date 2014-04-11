#ifndef SEARCH_C
#define SEARCH_C

#include <stdio.h>

#include "Search.h"

MazeArray searchArray;			// keeps track of whether or not robot was there previously
BOOL returning = FALSE;			// returning state means robot is going back to previous source

MazePoint searchStack[128];		// stack of branch locations
int searchStackPos = -1;		// stack pointer
Direction previousTravel[256];	// stack of previous turn directions
int previousTravelPos = -1;		// stack pointer

void malgo_explore_init()
{
	// zero out the search array
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for(int col = 0; col < MAZE_HEIGHT; col++) {
			searchArray[row][col] = 0;
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

	// if the maze is in a returning state, follow the stack back
	if (returning) {
		printf("returning...\n");
		if (previousTravelPos < 0) {
			returning = FALSE;
		}
		else {
			Direction returnDirection = previousTravel[previousTravelPos--];
			return returnDirection;
		}
	}

	// get surrounding wall map
	BOOL northWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, NORTH);
	BOOL eastWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, WEST);
	int total = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	// get the direction to go
	Direction toGo;

	// keep performing depth-first search
	if (total < 1) {
		printf("U-turn time!\n");

		returning = TRUE;
		return mazemap_rotation_to_direction(curDirection, BACKWARDS);	
	}

	// u-turn if there is nowhere to go
	else if (total > 1) {
		printf("multiple directions found\n");

		// loop through number of times we have hit this block
		BOOL wallArray[] = {northWall, eastWall, southWall, westWall};
		Direction directionArray[] = {NORTH, EAST, SOUTH, WEST};

		int numTimes = 0;
		for (int n = 0; n < 4; n++) {
			if (!wallArray[n]) {
				numTimes++;
			}

			if (numTimes == searchArray[yPos][xPos]) {
				toGo = directionArray[n];
				break;
			}
		}
	}

	// pursue the one direction the robot can go
	else {
		// find the direction to go
		if (!northWall) {
			toGo = NORTH;
		}
		else if (!eastWall) {
			toGo = EAST;
		}
		else if (!southWall) {
			toGo = SOUTH;
		}
		else {
			toGo = WEST;
		}

	}

	// increment the current position counter by one
	searchArray[yPos][xPos]++;

	// push that direction onto the stack
	previousTravel[++previousTravelPos] = toGo;

	// reutrn the desired direction
	printf("chosen direction: %i\n", (int)toGo);
	return toGo;
}

#endif
