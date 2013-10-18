#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <GL/gl.h>

#include "VirtualRobot.h"

VirtualRobot::VirtualRobot()
	: Robot(0, 0)
{
	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	this->rectangle = new Rectangle(yPos * blockWidthPX, yPos * blockWidthPX, robotSizePX, robotSizePX);
}

void VirtualRobot::draw() {
	// draw the robot red
	glColor3f(1.0f, 0.0f, 0.0f);
	rectangle->draw();
}

bool VirtualRobot::driveForward() {
	// try to move with the maze representation
	if (!Robot::driveForward()) {
		return false;
	}

	switch (direction) {
	case NORTH:
		rectangle->translate(0, VirtualMaze::getBlockWidthPX());
		break;
	case EAST:
		rectangle->translate(VirtualMaze::getBlockWidthPX(), 0);
		break;
	case SOUTH:
		rectangle->translate(0, -VirtualMaze::getBlockWidthPX());
		break;
	case WEST:
		rectangle->translate(-VirtualMaze::getBlockWidthPX(), 0);
		break;
	}

	return true;
}

#endif
