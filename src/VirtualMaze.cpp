#ifndef MAZE_CPP
#define MAZE_CPP

#include <GL/gl.h>
#include <stdio.h>

#include "VirtualMaze.h"

#include "define.h"
#include "Rectangle.h"

//
// constructors
//

VirtualMaze::VirtualMaze() {
	// for now, will generate a standard pattern
	//

	// init horizontal wall memory
	verticalWalls = new bool*[MAZE_HEIGHT];
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		verticalWalls[row] = new bool[MAZE_WIDTH+1];
	}

	// init vertical wall memory
	horizontalWalls = new bool*[MAZE_HEIGHT+1];
	for (int row = 0; row < (MAZE_HEIGHT+1); row++) {
		horizontalWalls[row] = new bool[MAZE_WIDTH];
	}

	// assign value to the walls
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH+1); col++) {
			//verticalWalls[row][col] = (col % 3 == 0);
			verticalWalls[row][col] = true;
		}
	}
	for (int row = 0; row < (MAZE_HEIGHT+1); row++) {
		for (int col = 0; col < (MAZE_WIDTH); col++) {
			//horizontalWalls[row][col] = (row % 3 == 0);
			horizontalWalls[row][col] = true;
		}
	}

	// now draw the walls
	rebuildWalls();
}

//
// main methods
//

// draws the maze
void VirtualMaze::draw() {
	// set the draw color to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// draw every wall in the wall list
	for (unsigned int n = 0; n < walls.size(); n++) {
		walls[n].draw();
	}
}

// recreates the walls based on the boolean arrays
void VirtualMaze::rebuildWalls() {
	// empty the vector
	walls.clear();

	// build the rows
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int column = 0; column < (MAZE_WIDTH+1); column++) {
			if (verticalWalls[row][column]) {
				int x = column * blockWidthPX - wallWidthPX / 2;
				int y = row * blockWidthPX;

				Rectangle rectangle(x, y, wallWidthPX, blockWidthPX);

				walls.push_back(rectangle);
			}
		}
	}

	// build the columns
	for (int row = 0; row < MAZE_HEIGHT+1; row++) {
		for (int column = 0; column < MAZE_WIDTH; column++) {
			if (horizontalWalls[row][column]) {
				int x = column * blockWidthPX;
				int y = row * blockWidthPX - wallWidthPX / 2;

				Rectangle rectangle(x, y, blockWidthPX, wallWidthPX);

				walls.push_back(rectangle);
			}
		}
	}
}

//
// static methods
//

int VirtualMaze::getBlockWidthPX() {
	return blockWidthPX;
}

#endif