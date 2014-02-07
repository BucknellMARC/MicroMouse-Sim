#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include "MazeAlgorithm.h"
#include "MazeMap.h"

// computes the flood fill for the first time (center is the target)
void malgo_floodfill_compute(MazeMap *mm, ff_map *in)
{
	// blanks out the array to null values
	memset(in, MALGO_FF_BAD, sizeof(ff_map));

	int[][] array = in->array;

	// set the inner four values to 0 (this is the target)
	int centerRow = MAZE_HEIGHT / 2;
	int centerCol = MAZE_WIDTH / 2;

	array[centerRow][centerCol] = 0;
	array[centerRow][centerCol + 1] = 0;
	array[centerRow + 1][centerCol] = 0;
	array[centerRow + 1][centerCol + 1] = 0;

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
				int nextCount = array[row][col + 1];
				bool wallExists = mazemap_doesWallExist(mm, col, row, EAST);
				if (!wallExists && nextCount != MALGO_FF_BAD) {
					array[row][col] = nextCount + 1;

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
				bool wallExists = mazemap_doesWallExist(mm, col, row, NORTH);	// bottom left is (0,0)
				if (!wallExists && nextCount != MALGO_FF_BAD) {
					array[row][col] = nextCount + 1;

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

#endif
