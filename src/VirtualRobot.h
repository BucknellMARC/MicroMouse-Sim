#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "Robot.h"
#include "VirtualMaze.h"

class VirtualRobot : public Robot {
private:
	Rectangle* rectangle;

	static const int robotSizePX = 5;

public:
	//
	// constructors
	//

	VirtualRobot();

	//
	// main methods
	//

	void draw();

	bool driveForward();
};

#endif
