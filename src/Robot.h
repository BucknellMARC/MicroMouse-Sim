#ifndef ROBOT_H
#define ROBOT_H

#include "VirtualMaze.h"

enum Direction {
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3
};

enum Rotation {
	LEFT,
	RIGHT,
	BACKWARDS
};

class Robot {
protected:
	int xPos, yPos;
	Direction direction;

protected:
	//
	// constructor
	//

	Robot();
	Robot(int xPos, int yPos);

public:
	//
	// main methods
	//

	void run();

	virtual void turn(Direction direction);
	virtual void turn(Rotation rotation);

	virtual bool driveForward();
};

#endif
