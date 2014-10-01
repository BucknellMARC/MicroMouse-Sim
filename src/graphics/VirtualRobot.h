#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "define.h"

extern "C" {
	#include "logic/Robot.h"
	#include "logic/FloodFill.h"
	#include "logic/Explore.h"
}

#include "VirtualMaze.h"

#define ROBOT_SIZE_PX 15

class VirtualRobot {
private:
	Robot robot;
	Rectangle* rectangle;
	VirtualMaze* virtualMaze;

	FFMap floodFillMap;

public:
	// constructor
	VirtualRobot(VirtualMaze* virtualMaze);

	// main methods

	void run();
	void feedSensorData();

	void draw();

	FFMapPtr getFloodFillMap();

	// destructor
	~VirtualRobot();
};

#endif
