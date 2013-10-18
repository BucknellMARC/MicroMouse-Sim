#ifndef VIRTUALMAZE_CPP
#define VIRTUALMAZE_CPP

/*
 * VirtualMaze is used to render the maze on screen it
 * contains Rectangles that draw walls and inherits
 * MazeMap which is what the robot will use to keep
 * track of where it is
 */

#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
	for (int row = 0; row < (MAZE_HEIGHT + 1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			horizontalWalls[row][col] = WALL;
		}
	}
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH + 1); col++) {
			verticalWalls[row][col] = WALL;
		}
	}

	// init the random number generator the
	// seed is just going to be the current time
	int seed = time(NULL);
	srand(seed);

	// free up some of the walls at random
	for (int row = 1; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH - 1); col++) {
			if ((rand() % 10) > 5) {
				horizontalWalls[row][col] = FREE;
			}
		}
	}
	for (int row = 0; row < (MAZE_HEIGHT - 1); row++) {
		for (int col = 1; col < MAZE_WIDTH; col++) {
			if ((rand() % 10) > 5) {
				verticalWalls[row][col] = FREE;
			}
		}
	}

	// start in the center and push location back
	int x = MAZE_WIDTH / 2;
	int y = MAZE_HEIGHT / 2;
	while (x != 0) {
		verticalWalls[y][x] = FREE;

		x--;
	}
	while (y != 0) {
		horizontalWalls[y][x] = FREE;

		y--;
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
		for (int column = 0; column < (MAZE_WIDTH + 1); column++) {
			if (verticalWalls[row][column] == WALL) {
				int x = column * blockWidthPX - wallWidthPX / 2;
				int y = row * blockWidthPX;

				Rectangle rectangle(x, y, wallWidthPX, blockWidthPX);

				walls.push_back(rectangle);
			}
		}
	}

	// build the columns
	for (int row = 0; row < (MAZE_HEIGHT + 1); row++) {
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
