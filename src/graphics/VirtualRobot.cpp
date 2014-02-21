#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <string.h>

extern "C" {
	#include "logic/Robot.h"
	#include "logic/MazeAlgorithm.h"
	#include "logic/MazeMap.h"
}

#include "VirtualRobot.h"
#include "Display.h"

VirtualRobot::VirtualRobot(VirtualMaze* virtualMaze)
{
	// create the robot using a blank maze map
	MazeMap* robotMM = (MazeMap*)calloc(1, sizeof(MazeMap));
	robot = robot_create(0, 0, robotMM);

	// bind the robot maze map to the virtualmaze
	virtualMaze->bindRobotMap(robotMM);


	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	int x = robot->xPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;
	int y = robot->yPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;

	this->rectangle = new Rectangle(x, y, robotSizePX, robotSizePX);

	// save the pointer to the virtual maze
	this->virtualMaze = virtualMaze;

	// compute the flood fill
	//malgo_floodfill_compute(virtualMaze->getMazeMap(), floodFillMap);
	//
	//robot->ffMap = floodFillMap;
}

void VirtualRobot::run() {

	// feed in the raw wall sensor input
	

	// run the algorithm
	//robot_runRightWall(robot);
	//robot_run_flood_fill(robot);

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
	//ff_draw(robot->ffMap);

}

FFMapPtr VirtualRobot::getFloodFillMap() {
	return robot->ffMap;
}

VirtualRobot::~VirtualRobot() {
	// destroy the robot
	robot_destroy(robot);
}

#endif
