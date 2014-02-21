#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include <stdlib.h>

#include "define.h"
#include "MazeMap.h"

MazeMap* mazemap_create() {
	MazeMap* mm = (MazeMap*)calloc(1, sizeof(MazeMap));

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

	// only return TRUE if we know the wall actually exists
	if (direction == NORTH || direction == SOUTH) {
		return mazeMap->horizWalls[yLook][xLook];
	}
	else {
		return mazeMap->vertWalls[yLook][xLook];
	}
}

// sets the desired wall to a new state
void mazemap_set_wall(MazeMap* mazeMap, BOOL state, int x, int y, Direction direction) {
	// get the proper look
	int xLook, yLook;
	BOOL success = mazemap_get_look_position(x, y, direction, &xLook, &yLook);

	if (!success) {
		return;
	}

	// assign to the proper array
	if (direction == NORTH || direction == SOUTH) {
		mazeMap->horizWalls[yLook][xLook] = state;
	}
	else {
		mazeMap->vertWalls[yLook][xLook] = state;
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

void mazemap_destroy(MazeMap* mm) {
	free(mm);
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
}

#endif
