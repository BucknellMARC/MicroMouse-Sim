#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "define.h"

#include "logic/Robot.h"
#include "VirtualMaze.h"

class VirtualRobot {
private:
	Robot* robot;
	Rectangle* rectangle;
	VirtualMaze* virtualMaze;

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
	//bool driveForward();

	void draw();

	// deconstructor
	~VirtualRobot();
};

#endif
