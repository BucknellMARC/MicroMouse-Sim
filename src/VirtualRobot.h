#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "Robot.h"
#include "VirtualMaze.h"

class VirtualRobot : public Robot {
private:
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

	void draw();

	bool lookForward();
	bool lookLeft();
	bool lookRight();

	bool driveForward();
};

#endif
