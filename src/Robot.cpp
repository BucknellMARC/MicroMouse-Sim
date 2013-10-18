#ifndef ROBOT_CPP
#define ROBOT_CPP

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
}

void Robot::run() {

}

void Robot::turn(Direction direction) {
	this->direction = direction;
}

void Robot::turn(Rotation rotation) {
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
		}
	}
	else {
		// if u-turn, just turn right twice..
		turn(RIGHT);
		turn(RIGHT);
	}
}

bool Robot::driveForward() {
	return true;
}

#endif

