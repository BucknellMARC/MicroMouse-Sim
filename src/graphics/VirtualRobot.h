#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "define.h"

extern "C" {
	#include "logic/Robot.h"
	#include "logic/FloodFill.h"
	#include "logic/Search.h"
}

#include "VirtualMaze.h"

class VirtualRobot {
private:
	Robot robot;
	Rectangle* rectangle;
	VirtualMaze* virtualMaze;

	FFMap floodFillMap;

	static const int robotSizePX = 15;

public:
	//
	// constructors
	//

	VirtualRobot(VirtualMaze* virtualMaze);

	//
	// main methods
	//

	void run();
	void feedSensorData();

	void draw();

	//
	// getters
	//

	FFMapPtr getFloodFillMap();

	// deconstructor
	~VirtualRobot();
};

#endif
