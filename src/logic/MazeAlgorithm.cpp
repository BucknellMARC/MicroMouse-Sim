#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include <string.h>

#include "MazeAlgorithm.h"
#include "MazeMap.h"

// computes the flood fill for the first time (center is the target)
// ** UNTESTED **
void malgo_floodfill_compute(MazeMap *mm, ff_map *in)
{
	// blanks out the array to null values
	memset(in, MALGO_FF_BAD, sizeof(ff_map));

	// set the inner four values to 0 (this is the target)
	int centerRow = MAZE_HEIGHT / 2;
	int centerCol = MAZE_WIDTH / 2;

	in->array[centerRow][centerCol] = 0;
	in->array[centerRow][centerCol + 1] = 0;
	in->array[centerRow + 1][centerCol] = 0;
	in->array[centerRow + 1][centerCol + 1] = 0;

	// now keep looping in each direction until the values have been populated
	bool isPopulated = false;
	while(!isPopulated) {

		// EAST/WEST
		int rowsPopulated = 0;
		for (int row = 0; row < MAZE_HEIGHT; row++) {
			int filledCells = 0;

			for (int col = 0; col < (MAZE_WIDTH-1); col++) {
				
				// see if there is an adjacent wall; if not and adjacent tile has a meaningful value,
				// then set current tile to one greater
				int nextCount = in->array[row][col + 1];
				bool wallExists = mazemap_doesWallExist(mm, col, row, EAST);
				if (!wallExists && nextCount != MALGO_FF_BAD) {
					in->array[row][col] = nextCount + 1;

					filledCells++;
				}

			}

			// if every single cell updated, then increment the number of populated rows
			if (filledCells == (MAZE_WIDTH-1)) {
				rowsPopulated++;
			}
		}

		// NORTH/SOUTH
		int colsPopulated = 0;
		for (int col = 0; col < MAZE_WIDTH; col++) {
			int filledCells = 0;

			for (int row = 0; row < (MAZE_HEIGHT-1); row++) {

				// see if there is an adjacent wall; if not and adjacent tile has a meaningful value,
				// then set current tile to one greaterint nextCount = array[row + 1][col];
				int nextCount = in->array[row + 1][col];
				bool wallExists = mazemap_doesWallExist(mm, col, row, NORTH);	// bottom left is (0,0)
				if (!wallExists && nextCount != MALGO_FF_BAD) {
					in->array[row][col] = nextCount + 1;

					filledCells++;
				}
			}

			// if every single cell updated, then increment the number of 
			if (filledCells == (MAZE_HEIGHT-1)) {
				colsPopulated++;
			}
		}

		// check to see if both the rows and the columns have been populated
		isPopulated = (rowsPopulated == MAZE_HEIGHT) & (colsPopulated == MAZE_WIDTH);
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

#endif
