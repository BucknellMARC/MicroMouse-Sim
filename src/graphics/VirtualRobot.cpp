#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <stdio.h>
#include <GL/gl.h>
#include <string.h>

#include "logic/Robot.h"
#include "VirtualRobot.h"
#include "Display.h"

VirtualRobot::VirtualRobot(VirtualMaze* virtualMaze)
{
	// create the robot
	robot = robot_create(0, 0, virtualMaze->getMazeMap());

	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	int x = robot->xPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;
	int y = robot->yPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;

	this->rectangle = new Rectangle(x, y, robotSizePX, robotSizePX);

	// save the pointer to the virtual maze
	this->virtualMaze = virtualMaze;

	// blank out the flood fill map
	memset(&floodFillMap, 0, sizeof(ff_map));
}

void VirtualRobot::run() {

	// run the algorithm
	robot_runRightWall(robot);

	// calculate and update the new position
	int blockWidthPX = VirtualMaze::getBlockWidthPX();
	int offset = blockWidthPX / 2 - robotSizePX / 2;

	int newX = blockWidthPX * robot->xPos + offset;
	int newY = blockWidthPX * robot->yPos + offset;
	rectangle->setPos(newX, newY);
}

/*
bool VirtualRobot::driveForward() {
	// try to move with the maze representation
	if (look(FORWARDS)) {
		return false;
	}

	// perform parent drive forward
	robot_driveForward(robot);

	// then move the rectangle
	switch (robot->direction) {
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
*/

void VirtualRobot::draw() {
	// draw the robot red
	rectangle->draw(1.0f, 0.0f, 0.0f);

	// draw the flood fill
	ff_draw(&floodFillMap);

}

ff_map *VirtualRobot::getFloodFillMap() {
	return &floodFillMap;
}

VirtualRobot::~VirtualRobot() {
	// destroy the robot
	robot_destroy(robot);
}

#endif
