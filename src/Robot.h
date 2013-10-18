#ifndef ROBOT_H
#define ROBOT_H

#include "define.h"
#include "MazeMap.h"

class Robot {
protected:
	// position and direction the robot is facing
	int xPos, yPos;
	Direction direction;

	MazeMap* mazeMap;

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

	Direction rotationToDirection(Rotation rotation);

	virtual bool lookForward()	= 0;
	virtual bool lookLeft()		= 0;
	virtual bool lookRight()	= 0;

	virtual void turn(Direction direction);
	virtual void turn(Rotation rotation);

	virtual bool driveForward();
};

#endif
