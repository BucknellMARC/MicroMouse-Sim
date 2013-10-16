#ifndef ROBOT_H
#define ROBOT_H

#include "VirtualMaze.h"

class Robot {
private:
	int xPos, yPos;
	VirtualMaze* maze;

public:
	//
	// constructor
	//

	Robot();
	Robot(int xPos, int yPos);
	Robot(int xPos, int yPos, VirtualMaze* maze);

	//
	// main methods
	//

	virtual void run();
};

#endif
