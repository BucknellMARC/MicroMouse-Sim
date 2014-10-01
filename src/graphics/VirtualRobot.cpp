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
#include "VirtualMaze.h"

VirtualRobot::VirtualRobot(VirtualMaze* virtualMaze)
{
	// create the robot
	robot = robot_create(0, 0);

	// bind the robot maze map to the virtualmaze
	virtualMaze->bindRobotMap(&robot.em.mazeMap);


	int blockWidthPX = VirtualMaze::getBlockWidthPX();

	int x = robot.pos.x * blockWidthPX + blockWidthPX/2 - ROBOT_SIZE_PX/2;
	int y = robot.pos.y * blockWidthPX + blockWidthPX/2 - ROBOT_SIZE_PX/2;

	this->rectangle = new Rectangle(x, y, ROBOT_SIZE_PX, ROBOT_SIZE_PX);

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
	int offset = blockWidthPX / 2 - ROBOT_SIZE_PX / 2;

	int newX = blockWidthPX * robot.pos.x + offset;
	int newY = blockWidthPX * robot.pos.y + offset;
	rectangle->setPos(newX, newY);
}

void VirtualRobot::feedSensorData() {
	// get the full map
	MazeMap* virtualMap = virtualMaze->getMazeMap();
	Point pos = robot.pos;

	// load in information about surroundings
	BOOL northWall = mm_is_wall(virtualMap, pos, NORTH);
	BOOL eastWall = mm_is_wall(virtualMap, pos, EAST);
	BOOL southWall = mm_is_wall(virtualMap, pos, SOUTH);
	BOOL westWall = mm_is_wall(virtualMap, pos, WEST);

	// plug the data from the virtual maze into the robot's maze map
	MazeMap* robotMap = &robot.em.mazeMap;
	mm_set_wall(robotMap, northWall, pos, NORTH);
	mm_set_wall(robotMap, eastWall, pos, EAST);
	mm_set_wall(robotMap, southWall, pos, SOUTH);
	mm_set_wall(robotMap, westWall, pos, WEST);
}

void VirtualRobot::draw() {
	// draw the robot yellow if exploring, red if solving
	if (robot.isExploring) {
		rectangle->draw(1.0f, 1.0f, 0.0f);
	}
	else {
		rectangle->draw(1.0f, 0.0f, 0.0f);

		// draw the flood fill once exploring is over
		VirtualMaze::drawFloodFill(robot.ffMap);
	}
}

FFMapPtr VirtualRobot::getFloodFillMap() {
	return robot.ffMap;
}

VirtualRobot::~VirtualRobot() {
}

#endif
