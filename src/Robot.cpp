#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <stdio.h>

#include "Robot.h"

//
// constructors
//

// default constructor
Robot::Robot()
	: Robot(0, 0)
{
	// init the position history and the floodmap
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			posHistory[row][col] = 0;
			floodMap[row][col] = 0;
		}
	}

	// init the wall map all false
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH - 1; col++) {
			vertWallMap[row][col] = false;
		}
	}
	for (int row = 0; row < MAZE_HEIGHT - 1; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			horizWallMap[row][col] = false;
		}
	}
}

// normal use constructor
Robot::Robot(int xPos, int yPos) {
	this->xPos = xPos;
	this->yPos = yPos;

	this->direction = EAST;
}

void Robot::runRightWall() {
	printf("--Robot::runRightWall()--\n");

	// turn right if the robot can...
	if (!look(RIGHT)) {
		printf("Turning right\n");
		turn(RIGHT);
	}

	// turn around if we are in front of a wall
	if (look(FORWARDS)) {
		printf("turning backwards...\n");
		turn(LEFT);
	}

	// try and drive forward
	driveForward();
}

void Robot::runFloodFill() {
	printf("--Robot::runFloodFill()--\n");

	// init the flood fill if it hasn't been
}

Direction Robot::rotationToDirection(Rotation rotation) {
	Direction direction = this->direction;

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
		}
	}

	return direction;
}

bool Robot::rotationToCoords(Rotation rotation, int* out) {
	// look forward
	// get direction to look
	Direction direct = rotationToDirection(rotation);
	int xCoord, yCoord;

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

bool Robot::look(Rotation rotation) {
	// get the direction
	Direction direction = rotationToDirection(rotation);
	int xLook, yLook;

	switch(direction) {
	case NORTH:
	case WEST:
		xLook = xPos;
		yLook = yPos;
		break;

	case EAST:
		xLook = xPos + 1;
		yLook = yPos;
		break;

	case SOUTH:
		xLook = xPos;
		yLook = yPos + 1;
		break;
	}

	// don't access the arrays if stuff is out of bounds
	if (xLook >= MAZE_WIDTH || yLook >= MAZE_HEIGHT) {
		return false;
	}

	// get data from proper location
	if (direction == NORTH || direction == SOUTH) {
		return vertWallMap[yLook][xLook];
	}
	else {
		return horizWallMap[yLook][xLook];
	}
}

void Robot::turn(Direction direction) {
	this->direction = direction;
}

void Robot::turn(Rotation rotation) {
	// set the new direction
	direction = rotationToDirection(rotation);
}

bool Robot::driveForward() {
	switch (direction) {
	case NORTH:
		yPos++;
		break;
	case EAST:
		xPos++;
		break;
	case SOUTH:
		yPos--;
		break;
	case WEST:
		xPos--;
		break;
	}

	// increment the history counter for that position
	posHistory[yPos][xPos]++;

	return true;
}

#endif

