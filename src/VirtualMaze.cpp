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
	// perform prim generation
	primGeneration();
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
// private methods
//

// prim's algorithm
void VirtualMaze::primGeneration() {
	// init the random number generator the
	// seed is just going to be the current time
	int seed = time(NULL);
	srand(seed);

	printf("Starting prim generation...\n");

	// wall out the entire maze
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH + 1); col++) {
			verticalWalls[row][col] = WALL;
		}
	}
	for (int row = 0; row < (MAZE_HEIGHT + 1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			horizontalWalls[row][col] = WALL;
		}
	}

	// init variable that keeps track of whether or not square is part of the maze
	bool partOfMaze[MAZE_HEIGHT][MAZE_WIDTH];
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			partOfMaze[row][col] = false;
		}
	}

	// holds list of walls active in the algorithm
	vector<Point> activeWallList;

	// add the first cell location to the active wall list
	Point zeroPoint;
	zeroPoint.x = 0;
	zeroPoint.y = 0;
	activeWallList.push_back(zeroPoint);

	// loop until the active wall list is zero
	while (activeWallList.size() > 0) {
		printf("Wall looping...\n");

		// get a random location from the wall list
		int currentPos = rand() % activeWallList.size();
		Point current = activeWallList[currentPos];

		printf("---Current Point---\n");
		printf("Pos: %i\n", currentPos);
		printf("X: %i\tY:%i\n", current.x, current.y);

		// lists the direction that the active spot can go in...
		vector<Direction> canGo;

		// figure out what is part of the maze and what is not
		if ((current.y + 1) < MAZE_HEIGHT && !partOfMaze[current.y + 1][current.x]) {
			canGo.push_back(NORTH);
		}
		if ((current.x + 1) < MAZE_WIDTH && !partOfMaze[current.y][current.x + 1]) {
			canGo.push_back(EAST);
		}
		if (current.y > 0 && !partOfMaze[current.y - 1][current.x]) {
			canGo.push_back(SOUTH);
		}
		if (current.x > 0 && !partOfMaze[current.y][current.x - 1]) {
			canGo.push_back(WEST);
		}

		// the DOF is just number of directions you can go
		int degreesOfFreedom = canGo.size();

		// if the degrees of freedom zero, then remove it from the list
		if (degreesOfFreedom == 0) {
			activeWallList.erase(activeWallList.begin() + currentPos);
		}
		else {
			// go in a random direction
			Direction direction = canGo[rand() % canGo.size()];

			// break down the wall between the two locations
			setWall(FREE, current.x, current.y, direction);

			// get the new destination
			Point destination = current;
			switch (direction) {
			case NORTH:
				destination.y++;
				break;
			case EAST:
				destination.x++;
				break;
			case SOUTH:
				destination.y--;
				break;
			case WEST:
				destination.x--;
				break;
			}

			// make the destination part of the maze
			partOfMaze[destination.y][destination.x] = true;

			// add it to the wall lsit
			activeWallList.push_back(destination);
		}
	}

	// rebuild the graphical walls
	rebuildWalls();
}

//
// static methods
//

int VirtualMaze::getBlockWidthPX() {
	return blockWidthPX;
}

#endif
