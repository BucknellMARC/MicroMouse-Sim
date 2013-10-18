#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <stdio.h>
#include <GL/gl.h>

#include "VirtualRobot.h"

VirtualRobot::VirtualRobot(VirtualMaze* virtualMaze)
	: Robot(0, 0)
{
	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	int x = xPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;
	int y = yPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;

	this->rectangle = new Rectangle(x, y, robotSizePX, robotSizePX);

	// save the pointer to the virtual maze
	this->virtualMaze = virtualMaze;
}

void VirtualRobot::draw() {
	// draw the robot red
	glColor3f(1.0f, 0.0f, 0.0f);
	rectangle->draw();
}

bool VirtualRobot::lookForward() {
	return virtualMaze->doesWallExist(xPos, yPos, direction);
}

bool VirtualRobot::lookLeft() {
	return virtualMaze->doesWallExist(xPos, yPos, rotationToDirection(LEFT));
}

bool VirtualRobot::lookRight() {
	return virtualMaze->doesWallExist(xPos, yPos, rotationToDirection(RIGHT));
}

bool VirtualRobot::driveForward() {
	// try to move with the maze representation
	if (lookForward()) {
		return false;
	}

	// perform parent drive forward
	Robot::driveForward();

	// then move the rectangle
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
