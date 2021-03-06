#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "define.h"
#include "MazeMap.h"

MazeMap mm_create() {
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

BOOL mm_is_wall(MazeMap* mazeMap, Point pos, Direction direction) {
	// get the wall from wall list
	int xLook, yLook;
	BOOL success = mm_get_look_position(pos, direction, &xLook, &yLook);

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

BOOL mm_is_wall_r(MazeMap* mazeMap, Point pos, Direction direction, Rotation rotation) {
	Direction fixedDirection = rotation_to_direction(direction, rotation);

	return mm_is_wall(mazeMap, pos, fixedDirection);
}

// sets the desired wall to a new state
void mm_set_wall(MazeMap* mazeMap, BOOL state, Point pos, Direction direction) {
	
	// get the proper array position, will return false if the value is out of bounds
	int xLook, yLook;
	BOOL success = mm_get_look_position(pos, direction, &xLook, &yLook);

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

BOOL mm_get_look_position(Point pos, Direction direction, int* xLook, int* yLook) {
	// derive the look position from the current position and direction
	switch (direction) {
	case NORTH:
	case EAST:
		*xLook = pos.x;
		*yLook = pos.y;
		break;

	case SOUTH:
		*xLook = pos.x;
		*yLook = pos.y - 1;
		break;

	case WEST:
		*xLook = pos.x - 1;
		*yLook = pos.y;
		break;
	}

	// there is a wall if we are looking out of bounds
	if (*xLook < 0 || *yLook < 0) {
		return FALSE;
	}

	// check for other random bounds
	if (direction == EAST && pos.x == (MAZE_WIDTH - 1)) {
		return FALSE;
	}
	if (direction == NORTH && pos.y == (MAZE_HEIGHT - 1)) {
		return FALSE;
	}


	return TRUE;
}

void mm_one_ahead_direction(Direction direction, Point* pos)
{
	switch(direction) {
	case EAST:
		//*x = *x + 1;
		pos->x = pos->x + 1;
		return;
	case SOUTH:
		//*y = *y - 1;
		pos->y = pos->y - 1;
		return;
	case WEST:
		//*x = *x - 1;
		pos->x = pos->x - 1;
		return;
	case NORTH:
		//*y = *y + 1;
		pos->y = pos->y + 1;
		return;

	default:
		printf("Error: Invalid direction!\n");
	}
}

//
// helper methods
//

Direction rotation_to_direction(Direction direction, Rotation rotation)
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

Rotation direction_to_rotation(Direction curDirection, Direction targetDirection)
{
	printf("Error: direction_to_rotation() not implemented!\n");
	return FORWARDS;
}

#endif
