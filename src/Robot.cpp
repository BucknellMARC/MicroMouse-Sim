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
}

// normal use constructor
Robot::Robot(int xPos, int yPos) {
	this->xPos = xPos;
	this->yPos = yPos;

	this->direction = EAST;

	this->mazeMap = new MazeMap();
}

void Robot::run() {
	printf("--Robot::run()--\n");

	// turn right if the robot can...
	if (!lookRight()) {
		printf("Turning right\n");
		turn(RIGHT);
	}

	// turn around if we are in front of a wall
	if (lookForward()) {
		printf("turning backwards...\n");
		turn(LEFT);
	}

	// try and drive forward
	driveForward();
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

	return true;
}

#endif

