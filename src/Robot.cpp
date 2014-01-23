#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <stdlib.h>
#include <stdio.h>

#include "Robot.h"

// default initializer
Robot* robot_create(int xPos, int yPos, MazeMap* mm)
{
	Robot* robot = (Robot*)calloc(1, sizeof(Robot));

	// assign the initial position to the robot
	robot->xPos = xPos;
	robot->yPos = yPos;

	robot->direction = EAST;

	robot->mazeMap = mm;

	return robot;
}

void robot_runRightWall(Robot* robot) {
	// turn right if you can
	if (robot_look(robot, RIGHT)) {
		robot_turn(robot, RIGHT);
	}

	if (!robot_look(robot, FORWARDS)) {
		robot_turn(robot, LEFT);
		return;
	}

	robot_driveForward(robot);
}

void robot_runFloodFill(Robot* robot) {
	printf("--Robot::runFloodFill()--\n");

	// init the flood fill if it hasn't been
}

Direction robot_rotationToDirection(Robot* robot, Rotation rotation) {
	// holds the direction that the lookup table converts to
	Direction direction = robot->direction;

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

/*
bool robot_rotationToCoords(Robot* robot, Rotation rotation, int* out) {
	// look forward
	// get direction to look
	Direction direct = robot_rotationToDirection(robot, rotation);
	int xCoord, yCoord;

	// pull the positions from the robot
	int xPos = robot->xPos;
	int yPos = robot->yPos;

	switch(direct) {
	case NORTH:
		xCoord = xPos;
		yCoord = yPos - 1;
		break;

	case EAST:
		xCoord = xPos + 1;
		yCoord = yPos;
		break;

	case SOUTH:
		xCoord = xPos;
		yCoord = yPos + 1;
		break;

	case WEST:
		xCoord = xPos - 1;
		yCoord = yPos;
		break;
	}

	// if the coordinates are still in the bounds, return meaningful result
	if (xCoord > 0 && xCoord < MAZE_WIDTH &&
			yCoord > 0 && yCoord < MAZE_HEIGHT) {
		out[0] = xCoord;
		out[1] = yCoord;

		return true;
	}

	// otherwise, the coordinates were out of bounds
	return false;
}
*/

bool robot_look(Robot* robot, Rotation rotation) {
	// get the direction
	Direction direction = robot_rotationToDirection(robot, rotation);

	return !mazemap_doesWallExist(robot->mazeMap, robot->xPos, robot->yPos, direction);

	/*
	int xPos = robot->xPos;
	int yPos = robot->yPos;

	switch(direction) {
	case NORTH:
		xLook = xPos;
		yLook = yPos - 1;
		break;

	case WEST:
		xLook = xPos - 1;
		yLook = yPos;
		break;

	case EAST:
	case SOUTH:
		xLook = xPos;
		yLook = yPos;
		break;

	default:
		printf("Error: Robot is in an unexpected state!\n");
	}

	// don't access the arrays if stuff is out of bounds
	if (xLook > -1 || yLook > -1) {
		return false;
	}

	// get data from proper location
	if (direction == NORTH || direction == SOUTH) {
		return !robot->mazeMap->vertWalls[yLook][xLook];
	}
	else {
		return !robot->mazeMap->horizWalls[yLook][xLook];
	}
	*/
}

void robot_turn(Robot* robot, Direction direction) {
	robot->direction = direction;
}

void robot_turn(Robot* robot, Rotation rotation) {
	// set the new direction
	//printf("Original direction: %d\n", (int)robot->direction);

	robot->direction = robot_rotationToDirection(robot, rotation);

	//printf("New Direction: %d\n\n", (int)robot->direction);
}

bool robot_driveForward(Robot* robot) {
	Direction direction = robot->direction;

	printf("X: %d\tY:%d\n", robot->xPos, robot->yPos);
	printf("Forwards: %d\nLeft: %d\nRight: %d\n", robot_look(robot, FORWARDS), robot_look(robot, LEFT), robot_look(robot, RIGHT));

	switch (direction) {
	case NORTH:
		robot->yPos++;
		break;

	case EAST:
		robot->xPos++;
		break;

	case SOUTH:
		robot->yPos--;
		break;

	case WEST:
		robot->xPos--;
		break;

	default:
		printf("Error: Robot is in an unexpected state!\n");
	}

	// increment the history counter for that position
	//robot->posHistory[robot->yPos][robot->xPos]++;

	return true;
}

void robot_destroy(Robot* robot) {
	free(robot);
}

#endif

