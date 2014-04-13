#ifndef VIRTUALROBOT_CPP
#define VIRTUALROBOT_CPP

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <string.h>

extern "C" {
	#include "logic/Robot.h"
	#include "logic/FloodFill.h"
	#include "logic/Explore.h"
	#include "logic/MazeMap.h"
}

#include "VirtualRobot.h"
#include "Display.h"

VirtualRobot::VirtualRobot(VirtualMaze* virtualMaze)
{
	// create the robot
	robot = robot_create(0, 0);

	// bind the robot maze map to the virtualmaze
	virtualMaze->bindRobotMap(&robot.mazeMap);


	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	int x = robot.xPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;
	int y = robot.yPos * blockWidthPX + blockWidthPX/2 - robotSizePX/2;

	this->rectangle = new Rectangle(x, y, robotSizePX, robotSizePX);

	// save the pointer to the virtual maze
	this->virtualMaze = virtualMaze;
}

void VirtualRobot::run() {

	// feed in the raw wall sensor input
	feedSensorData();

	// run the robot drive code
	robot_run(&robot);

	// calculate and update the new position
	int blockWidthPX = VirtualMaze::getBlockWidthPX();
	int offset = blockWidthPX / 2 - robotSizePX / 2;

	int newX = blockWidthPX * robot.xPos + offset;
	int newY = blockWidthPX * robot.yPos + offset;
	rectangle->setPos(newX, newY);
}

void VirtualRobot::feedSensorData() {
	// get the full map
	MazeMap* virtualMap = virtualMaze->getMazeMap();
	int x = robot.xPos;
	int y = robot.yPos;

	// load in information about surroundings
	BOOL northWall = mazemap_does_wall_exist(virtualMap, x, y, NORTH);
	BOOL eastWall = mazemap_does_wall_exist(virtualMap, x, y, EAST);
	BOOL southWall = mazemap_does_wall_exist(virtualMap, x, y, SOUTH);
	BOOL westWall = mazemap_does_wall_exist(virtualMap, x, y, WEST);

	// plug the data from the virtual maze into the robot's maze map
	MazeMap* robotMap = &robot.mazeMap;
	mazemap_set_wall(robotMap, northWall, x, y, NORTH);
	mazemap_set_wall(robotMap, eastWall, x, y, EAST);
	mazemap_set_wall(robotMap, southWall, x, y, SOUTH);
	mazemap_set_wall(robotMap, westWall, x, y, WEST);
}

void VirtualRobot::draw() {
	// draw the robot yellow if exploring, red if solving
	if (robot.isExploring) {
		rectangle->draw(1.0f, 1.0f, 0.0f);
	}
	else {
		rectangle->draw(1.0f, 0.0f, 0.0f);

		// draw the flood fill once exploring is over
		ff_draw(robot.ffMap);
	}
}

FFMapPtr VirtualRobot::getFloodFillMap() {
	return robot.ffMap;
}

VirtualRobot::~VirtualRobot() {
}

#endif
