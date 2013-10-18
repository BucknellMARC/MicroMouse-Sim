#ifndef VIRTUALMAZE_CPP
#define VIRTUALMAZE_CPP

#include <GL/gl.h>
#include <stdio.h>
#include <vector>
using namespace std;

#include "VirtualMaze.h"

#include "define.h"
#include "Rectangle.h"

//
// constructors
//

VirtualMaze::VirtualMaze()
	: MazeMap() {
	// for now, will generate a standard pattern
	//

	// assign value to the walls
	for (int row = 0; row < (MAZE_HEIGHT+1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			horizontalWalls[row][col] = WALL;
		}
	}
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH+1); col++) {
			verticalWalls[row][col] = WALL;
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
			if (verticalWalls[row][column] == WALL) {
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
			if (horizontalWalls[row][column] == WALL) {
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
