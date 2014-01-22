#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include "define.h"
#include "MazeMap.h"

MazeMap::MazeMap() {

}

bool MazeMap::doesWallExist(int x, int y, Direction direction) {
	// get the wall from wall list
	int xLook, yLook;
	bool success = getLookPositions(x, y, direction, &xLook, &yLook);

	// if the look position was out of bounds, there is a wall
	if (!success) {
		return true;
	}

	// only return true if we know the wall actually exists
	if (direction == NORTH || direction == SOUTH) {
		return horizWalls[yLook][xLook];
	}
	else {
		return vertWalls[yLook][xLook];
	}
}

// sets the desired wall to a new state
void MazeMap::setWall(bool state, int x, int y, Direction direction) {
	// get the proper look
	int xLook, yLook;
	bool success = getLookPositions(x, y, direction, &xLook, &yLook);

	if (!success) {
		return;
	}

	// assign to the proper array
	if (direction == NORTH || direction == SOUTH) {
		horizWalls[yLook][xLook] = state;
	}
	else {
		vertWalls[yLook][xLook] = state;
	}
}

bool MazeMap::getLookPositions(int x, int y, Direction direction, int* xLook, int* yLook) {
	// derive the look position from the current position and direction
	switch (direction) {
	case NORTH:
	case EAST:
		*xLook = x;
		*yLook = y;
		break;

	case SOUTH:
		*xLook = x;
		*yLook = y - 1;
		break;

	case WEST:
		*xLook = x - 1;
		*yLook = y;
		break;
	}

	// there is a wall if we are looking out of bounds
	if (*xLook < 0 || *yLook < 0) {
		return false;
	}

	// check for other random bounds
	if (direction == EAST && x == (MAZE_WIDTH - 1)) {
		return false;
	}
	if (direction == NORTH && y == (MAZE_HEIGHT - 1)) {
		return false;
	}


	return true;
}

#endif
