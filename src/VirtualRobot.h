#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "define.h"

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

	bool look(Rotation rotation);

	bool driveForward();
};

#endif
