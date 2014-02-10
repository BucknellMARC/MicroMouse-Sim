#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <stdio.h>
#include <GL/gl.h>
#include <string.h>

#include "logic/Robot.h"
#include "logic/MazeAlgorithm.h"
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

	// compute the flood fill
	malgo_floodfill_compute(virtualMaze->getMazeMap(), &floodFillMap);

	robot->map = floodFillMap;
}

void VirtualRobot::run() {

	// run the algorithm
	//robot_runRightWall(robot);
	robot_runFloodFill(robot);

	// calculate and update the new position
	int blockWidthPX = VirtualMaze::getBlockWidthPX();
	int offset = blockWidthPX / 2 - robotSizePX / 2;

	int newX = blockWidthPX * robot->xPos + offset;
	int newY = blockWidthPX * robot->yPos + offset;
	rectangle->setPos(newX, newY);
}

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
