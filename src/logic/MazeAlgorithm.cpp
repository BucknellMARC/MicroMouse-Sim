#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include <string.h>

#include "MazeAlgorithm.h"
#include "MazeMap.h"

// computes the flood fill for the first time (center is the target)
void malgo_floodfill_compute(MazeMap *mm, ff_map *in)
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
	bool isPopulated = false;
	//while(!isPopulated) {
	for (int dumbshit = 0; dumbshit < 100000; dumbshit++) {

		// SOUTH to NORTH
		for (int row = 0; row < (MAZE_HEIGHT-1); row++) {
			for (int col = 0; col < MAZE_WIDTH; col++) {
				
				int curVal = in->array[row][col];
				if (curVal != MALGO_FF_BAD || curVal == 0) {
					continue;
				}

				bool wallExists = mazemap_doesWallExist(mm, col, row, NORTH);	// bottom left is (0,0)
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

				bool wallExists = mazemap_doesWallExist(mm, col, row, SOUTH);	// bottom left is (0,0)
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

				bool wallExists = mazemap_doesWallExist(mm, col, row, EAST);	// bottom left is (0,0)
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

				bool wallExists = mazemap_doesWallExist(mm, col, row, WEST);	// bottom left is (0,0)
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
void malgo_floodfill_recompute_target(int targetX, int targetY, ff_map *in)
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
Direction malgo_floodfill_suggest_turn(int xPos, int yPos, ff_map *map)
{
	int east = 0; int south = 1; int west = 2; int east = 3;
	int minVal = 0xffffffff;
	int max = 0;

	// check east
	if (xPos + 1 < MAZE_WIDTH && map->array[yPos][xPos + 1] < minVal) {
		minVal = map->array[yPos][xPos + 1];
		max = east;
	}

	// south
	if (yPos - 1 > -1 && map->array[yPos - 1][xPos] < minVal) {
		minVal = map->array[yPos - 1][xPos];
		max = south;
	}

	// west
	if (xPos - 1 > -1 && map->array[yPos][xPos - 1] < minVal) {
		minVal = map->array[yPos][xPos - 1];
		max = west;
	}

	// and north
	if (yPos + 1 < MAZE_HEIGHT && map->array[yPos + 1][xPos] < max) {
		minVal = map->array[yPos + 1][xPos];
		max = north;
	}

	switch(max) {
		case 0:
			return EAST;
		case 1: 
			return SOUTH;
		case 2:
			return WEST;
		case 3:
			return EAST;
	}
}

#endif
