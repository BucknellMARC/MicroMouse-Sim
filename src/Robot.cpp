#ifndef ROBOT_CPP
#define ROBOT_CPP

#include "Robot.h"

//
// constructors
//

// default constructor
Robot::Robot() {
	this->xPos = 0;
	this->yPos = 0;

	this->maze = new VirtualMaze();
}

// normal use constructor
Robot::Robot(int xPos, int yPos) {
	this->xPos = xPos;
	this->yPos = yPos;

	this->maze = new VirtualMaze();
}

// hands a premade maze object
Robot::Robot(int xPos, int yPos, VirtualMaze* maze) {
	this->xPos = xPos;
	this->yPos = yPos;

	this->maze = maze;
}

void Robot::run() {

}

#endif

