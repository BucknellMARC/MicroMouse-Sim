#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include <stdio.h>
#include <string.h>

#include "define.h"
#include "MazeAlgorithm.h"
#include "MazeMap.h"

// computes the flood fill for the first time (center is the target)
void malgo_floodfill_compute(MazeMap* mm, ff_map* in)
{
	// blanks out the array to null values
	memset(in, MALGO_FF_BAD, sizeof(ff_map));

	// set the inner four values to 0 (this is the target)
	int centerRow = MAZE_HEIGHT / 2 - 1;
	int centerCol = MAZE_WIDTH / 2 - 1;

	in->array[centerRow][centerCol] = 0;
	in->array[centerRow][centerCol + 1] = 0;
	in->array[centerRow + 1][centerCol] = 0;
	in->array[centerRow + 1][centerCol + 1] = 0;

	// now keep looping in each direction until the values have been populated
	BOOL isPopulated = FALSE;
	//while(!isPopulated) {
	for (int stupid = 0; stupid < 100000; stupid++) {

		// SOUTH to NORTH
		for (int row = 0; row < (MAZE_HEIGHT-1); row++) {
			for (int col = 0; col < MAZE_WIDTH; col++) {
				
				int curVal = in->array[row][col];
				if (curVal != MALGO_FF_BAD || curVal == 0) {
					continue;
				}

				BOOL wallExists = mazemap_does_wall_exist(mm, col, row, NORTH);	// bottom left is (0,0)
				if (wallExists) {
					continue;
				}

				// get the value of the next column
				int nextVal = in->array[row + 1][col];

				// if the next value isn't bad, set the current one to it + 1
				if (nextVal != MALGO_FF_BAD) {
					in->array[row][col] = nextVal + 1;
				}
			}
		}

		// NORTH to SOUTH
		for (int row = MAZE_HEIGHT-1; row > 0; row--) {
			for (int col = 0; col < MAZE_WIDTH; col++) {
				
				int curVal = in->array[row][col];
				if (curVal != MALGO_FF_BAD || curVal == 0) {
					continue;
				}

				BOOL wallExists = mazemap_does_wall_exist(mm, col, row, SOUTH);	// bottom left is (0,0)
				if (wallExists) {
					continue;
				}

				// get next value
				int nextVal = in->array[row - 1][col];

				if (nextVal != MALGO_FF_BAD) {
					in->array[row][col] = nextVal + 1;
				}
			}
		}

		// WEST to EAST
		for (int row = 0; row < MAZE_HEIGHT; row++) {
			for (int col = 0; col < (MAZE_WIDTH-1); col++) {
				
				int curVal = in->array[row][col];
				if (curVal != MALGO_FF_BAD || curVal == 0) {
					continue;
				}

				BOOL wallExists = mazemap_does_wall_exist(mm, col, row, EAST);	// bottom left is (0,0)
				if (wallExists) {
					continue;
				}

				// get next val
				int nextVal = in->array[row][col + 1];

				if (nextVal != MALGO_FF_BAD) {
					in->array[row][col] = nextVal + 1;
				}
			}
		}

		// EAST to WEST
		for (int row = 0; row < MAZE_HEIGHT; row++) {
			for (int col = MAZE_WIDTH-1; col > 0; col--) {

				int curVal = in->array[row][col];
				if (curVal != MALGO_FF_BAD || curVal == 0) {
					continue;
				}

				BOOL wallExists = mazemap_does_wall_exist(mm, col, row, WEST);	// bottom left is (0,0)
				if (wallExists) {
					continue;
				}

				// get the next val
				int nextVal = in->array[row][col - 1];

				if (nextVal != MALGO_FF_BAD) {
					in->array[row][col] = nextVal + 1;
				}
			}
		}
	}
}

// retargets the flood fill map
// ** UNTESTED **	-- this will be wrong with the middle zero blocks
void malgo_floodfill_recompute_target(int targetX, int targetY, ff_map* in)
{
	// find the current target
	int currentX = MALGO_FF_BAD;
	int currentY = MALGO_FF_BAD;
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			int value = in->array[row][col];

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
	int difference = in->array[currentY][currentX];

	// displace the rest of the array
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {

			// make sure the value is always positive
			int curValue = in->array[row][col];
			if (difference > curValue) {
				in->array[row][col] = difference - curValue;
			}
			else {
				in->array[row][col] = curValue - difference;
			}
		}
	}
}

// uses floodfill to determine where to go
Direction malgo_floodfill_suggest(int xPos, int yPos, MazeMap *mazeMap, ff_map* ffMap)
{
	int minVal =  100000;
	Direction minDir = EAST;

	BOOL eastWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, EAST);
	BOOL southWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, WEST);
	BOOL northWall = mazemap_does_wall_exist(mazeMap, xPos, yPos, NORTH);

	int eastVal = 10000; int southVal = 10000; int westVal = 10000; int northVal = 10000;
	if (!eastWall) {
		eastVal = ffMap->array[yPos][xPos + 1];
	}
	if (!southWall) {
		southVal = ffMap->array[yPos - 1][xPos];
	}
	if (!westWall) {
		westVal = ffMap->array[yPos][xPos - 1];
	}
	if (!northWall) {
		northVal = ffMap->array[yPos + 1][xPos];
	}

	//printf("East: %d", eastWall);
	//printf("South: %d", southWall);
	//printf("West: %d", westWall);
	//printf("North: %d", northWall);

	printf("E: %d, S: %d, W: %d, N: %d\n", eastWall, southWall, westWall, northWall);
	printf("E: %d, S: %d, W: %d, N: %d\n", eastVal, southVal, westVal, northVal);

	if (!eastWall && eastVal < minVal) {
		printf("east is min\n");
		minDir = EAST;
		minVal = eastVal;
	}
	if (!southWall && southVal < minVal) {
		printf("south is min\n");
		minDir = SOUTH;
		minVal = southVal;
	}
	if (!westWall && westVal < minVal) {
		printf("west is min\n");
		minDir = WEST;
		minVal = westVal;
	}
	if (!northWall && northVal < minVal) {
		printf("north is min\n");
		minDir = NORTH;
	}

	return minDir;
}

#endif
