#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include <stdio.h>
#include <string.h>

#include "define.h"
#include "FloodFill.h"
#include "MazeMap.h"

// computes the flood fill for the first time (center is the target)
void malgo_floodfill_compute(MazeMap* mm, FFMapPtr in)
{
	// blanks out the array to null values
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			in[row][col] = MALGO_FF_BAD;
		}
	}

	// set the inner four values to 0 (this is the target)
	int centerRow = MAZE_HEIGHT / 2 - 1;
	int centerCol = MAZE_WIDTH / 2 - 1;

	in[centerRow][centerCol] = 0;
	in[centerRow][centerCol + 1] = 0;
	in[centerRow + 1][centerCol] = 0;
	in[centerRow + 1][centerCol + 1] = 0;

	// now keep looping in each direction until the values have been populated
	BOOL hasCompletedNeighbor = TRUE;
	while (hasCompletedNeighbor) {
		hasCompletedNeighbor = FALSE;

		// SOUTH to NORTH
		for (int row = 0; row < (MAZE_HEIGHT-1); row++) {
			for (int col = 0; col < MAZE_WIDTH; col++) {
				BOOL complete = malgo_floodfill_compute_pull_neighbor(row, col, NORTH, mm, in);

				if (complete) {
					hasCompletedNeighbor = TRUE;
				}
			}
		}

		// NORTH to SOUTH
		for (int row = MAZE_HEIGHT-1; row > 0; row--) {
			for (int col = 0; col < MAZE_WIDTH; col++) {
				BOOL complete = malgo_floodfill_compute_pull_neighbor(row, col, SOUTH, mm, in);

				if (complete) {
					hasCompletedNeighbor = TRUE;
				}
			}
		}

		// WEST to EAST
		for (int row = 0; row < MAZE_HEIGHT; row++) {
			for (int col = 0; col < (MAZE_WIDTH-1); col++) {
				BOOL complete = malgo_floodfill_compute_pull_neighbor(row, col, EAST, mm, in);

				if (complete) {
					hasCompletedNeighbor = TRUE;
				}
			}
		}

		// EAST to WEST
		for (int row = 0; row < MAZE_HEIGHT; row++) {
			for (int col = MAZE_WIDTH-1; col > 0; col--) {
				BOOL complete = malgo_floodfill_compute_pull_neighbor(row, col, WEST, mm, in);

				if (complete) {
					hasCompletedNeighbor = TRUE;
				}
			}
		}
	}
}

BOOL malgo_floodfill_compute_pull_neighbor(int row, int col, Direction direction, MazeMap* mm, FFMapPtr in)
{
	int curVal = in[row][col];
	if (curVal != MALGO_FF_BAD || curVal == 0) {
		return FALSE;
	}

	BOOL wallExists = mazemap_does_wall_exist(mm, col, row, direction);	// bottom left is (0,0)
	if (wallExists) {
		return FALSE;
	}

	// get the next val
	int nextVal;
	switch (direction) {
	case EAST:
		nextVal = in[row][col + 1];
		break;
	case SOUTH:
		nextVal = in[row - 1][col];
		break;
	case WEST:
		nextVal = in[row][col - 1];
		break;
	case NORTH:
		nextVal = in[row + 1][col];
		break;

	default:
		printf("Error: Invalid direction specified!\n");
	}

	if (nextVal != MALGO_FF_BAD) {
		in[row][col] = nextVal + 1;

		return TRUE;
	}

	return FALSE;
}

// retargets the flood fill map
// ** UNTESTED **	-- this will be wrong with the middle zero blocks
void malgo_floodfill_recompute_target(int targetX, int targetY, FFMapPtr in)
{
	// find the current target
	int currentX = MALGO_FF_BAD;
	int currentY = MALGO_FF_BAD;
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			int value = in[row][col];

			if (value == 0) {
				currentX = col;
				currentY = row;

				break;
			}
		}

		// if inner forloop found a match, break out of this one
		if (currentX != MALGO_FF_BAD) {
			break;
		}
	}

	// the new difference will be the current value of the new target
	int difference = in[currentY][currentX];

	// displace the rest of the array
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {

			// make sure the value is always positive
			int curValue = in[row][col];
			if (difference > curValue) {
				in[row][col] = difference - curValue;
			}
			else {
				in[row][col] = curValue - difference;
			}
		}
	}
}

// uses floodfill to determine where to go
Direction malgo_floodfill_suggest(int xPos, int yPos, MazeMap *mazeMap, FFMapPtr ffMap)
{
	int minVal =  100000;
	Direction minDir = EAST;

	BOOL eastWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, WEST);
	BOOL northWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, NORTH);

	int eastVal = 10000; int southVal = 10000; int westVal = 10000; int northVal = 10000;
	if (!eastWall) {
		eastVal = ffMap[yPos][xPos + 1];
	}
	if (!southWall) {
		southVal = ffMap[yPos - 1][xPos];
	}
	if (!westWall) {
		westVal = ffMap[yPos][xPos - 1];
	}
	if (!northWall) {
		northVal = ffMap[yPos + 1][xPos];
	}

	if (!eastWall && eastVal < minVal) {
		minDir = EAST;
		minVal = eastVal;
	}
	if (!southWall && southVal < minVal) {
		minDir = SOUTH;
		minVal = southVal;
	}
	if (!westWall&& westVal < minVal) {
		minDir = WEST;
		minVal = westVal;
	}
	if (!northWall && northVal < minVal) {
		minDir = NORTH;
	}

	return minDir;
}

#endif
