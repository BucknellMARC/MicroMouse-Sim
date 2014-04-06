#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "define.h"
#include "MazeMap.h"

MazeMap mazemap_create() {
	MazeMap mm;
	memset(&mm, 0, sizeof(MazeMap));

	// inits all the walls to the UNKNOWN state
	for (int row = 0; row < (MAZE_HEIGHT - 1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			mm.horizWalls[row][col] = UNKNOWN;
		}
	}
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH - 1); col++) {
			mm.vertWalls[row][col] = UNKNOWN;
		}
	}

	return mm;
}

BOOL mazemap_does_wall_exist(MazeMap* mazeMap, int x, int y, Direction direction) {
	// get the wall from wall list
	int xLook, yLook;
	BOOL success = mazemap_get_look_position(x, y, direction, &xLook, &yLook);

	// if the look position was out of bounds, there is a wall
	if (!success) {
		return TRUE;
	}

	// returns true only if we know for certain that there is no wall
	if (direction == NORTH || direction == SOUTH) {
		return (mazeMap->horizWalls[yLook][xLook] != NOWALL);
	}
	else {
		return (mazeMap->vertWalls[yLook][xLook] != NOWALL);
	}
}

BOOL mazemap_does_wall_exist_r(MazeMap* mazeMap, int x, int y, Direction direction, Rotation rotation) {
	Direction fixedDirection = mazemap_rotation_to_direction(direction, rotation);

	return mazemap_does_wall_exist(mazeMap, x, y, fixedDirection);
}

// sets the desired wall to a new state
void mazemap_set_wall(MazeMap* mazeMap, BOOL state, int x, int y, Direction direction) {
	
	// get the proper array position, will return false if the value is out of bounds
	int xLook, yLook;
	BOOL success = mazemap_get_look_position(x, y, direction, &xLook, &yLook);

	if (!success) {
		return;
	}

	WallState theRealState = NOWALL;
	if (state) {
		theRealState = WALL;
	}

	// assign to the proper array
	if (direction == NORTH || direction == SOUTH) {
		mazeMap->horizWalls[yLook][xLook] = theRealState;
	}
	else {
		mazeMap->vertWalls[yLook][xLook] = theRealState;
	}
}

BOOL mazemap_get_look_position(int x, int y, Direction direction, int* xLook, int* yLook) {
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
		return FALSE;
	}

	// check for other random bounds
	if (direction == EAST && x == (MAZE_WIDTH - 1)) {
		return FALSE;
	}
	if (direction == NORTH && y == (MAZE_HEIGHT - 1)) {
		return FALSE;
	}


	return TRUE;
}

//
// helper methods
//

Direction mazemap_rotation_to_direction(Direction direction, Rotation rotation)
{
	if (rotation == LEFT) {
		switch (direction) {
		case NORTH:
			direction = WEST;
			break;

		case EAST:
			direction = NORTH;
			break;

		case SOUTH:
			direction = EAST;
			break;

		case WEST:
			direction = SOUTH;
			break;

		default:
			printf("Error: Robot is in an unexpected state!\n");
		}
	}
	else if (rotation == RIGHT) {
		switch (direction) {
		case NORTH:
			direction = EAST;
			break;

		case EAST:
			direction = SOUTH;
			break;

		case SOUTH:
			direction = WEST;
			break;

		case WEST:
			direction = NORTH;
			break;

		default:
			printf("Error: Robot is in an unexpected state!\n");
		}
	}
	else if (rotation == BACKWARDS) {
		switch (direction) {
		case NORTH:
			direction = SOUTH;
			break;

		case EAST:
			direction = WEST;
			break;

		case SOUTH:
			direction = NORTH;
			break;

		case WEST:
			direction = EAST;
			break;

		default:
			printf("Error: Robot is in an unexpected state!\n");
		}
	}

	return direction;
}

Rotation mazemap_direction_to_rotation(Direction curDirection, Direction targetDirection)
{
	printf("Error: mazemap_direction_to_rotation() not implemented!\n");
	return FORWARDS;
}

void mazemap_one_ahead_direction(Direction direction, int* x, int* y)
{
	switch(direction) {
	case EAST:
		*x = *x + 1;
		return;
	case SOUTH:
		*y = *y - 1;
		return;
	case WEST:
		*x = *x - 1;
		return;
	case NORTH:
		*y = *y + 1;
		return;

	default:
		printf("Error: Invalid direction!\n");
	}
}

#endif
