#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include "define.h"
#include "MazeMap.h"

MazeMap::MazeMap() {
	// init the memory space for the wall states
	horizontalWalls = new WallState*[MAZE_HEIGHT + 1];
	for (int n = 0; n < (MAZE_HEIGHT + 1); n++) {
		horizontalWalls[n] = new WallState[MAZE_WIDTH];
	}

	verticalWalls = new WallState*[MAZE_HEIGHT];
	for (int n = 0; n < MAZE_HEIGHT; n++) {
		verticalWalls[n] = new WallState[MAZE_WIDTH + 1];
	}

	// now initialize everything in the unknown state
	for (int row = 0; row < (MAZE_HEIGHT + 1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			horizontalWalls[row][col] = UNKNOWN;
		}
	}
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH + 1); col++) {
			verticalWalls[row][col] = UNKNOWN;
		}
	}
}

bool MazeMap::doesWallExist(int x, int y, Direction direction) {
	WallState wallState;

	// get the wall from wall list
	switch (direction) {
	case NORTH:
		wallState = horizontalWalls[y+1][x];
		break;
	case EAST:
		wallState = verticalWalls[y][x+1];
		break;
	case SOUTH:
		wallState = horizontalWalls[y][x];
		break;
	case WEST:
		wallState = verticalWalls[y][x];
		break;
	}

	// only return true if we know the wall actually exists
	return (wallState == WALL);
}

// sets the desired wall to a new state
void MazeMap::setWall(WallState state, int x, int y, Direction direction) {
	// set the proper thing depending on direction
	switch (direction) {
	case NORTH:
		horizontalWalls[y+1][x] = state;
		break;
	case EAST:
		verticalWalls[y][x+1] = state;
		break;
	case SOUTH:
		horizontalWalls[y][x] = state;
		break;
	case WEST:
		verticalWalls[y][x] = state;
		break;
	}
}

#endif
