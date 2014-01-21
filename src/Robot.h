#ifndef ROBOT_H
#define ROBOT_H

#include "define.h"
#include "MazeMap.h"

class Robot {
protected:
	// position and direction the robot is facing
	int xPos, yPos;
	Direction direction;

	int posHistory[MAZE_HEIGHT][MAZE_WIDTH];
	int floodMap[MAZE_HEIGHT][MAZE_WIDTH];			// flood map holds distanced to target location

	bool vertWallMap[MAZE_HEIGHT][MAZE_WIDTH-1];	// vertical walls are between grid spaces
	bool horizWallMap[MAZE_HEIGHT-1][MAZE_WIDTH];	// horiz walls go across a grid space

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

	// movement algorithms
	void runRightWall();
	void runFloodFill();

	Direction	rotationToDirection(Rotation rotation);
	bool		rotationToCoords(Rotation rotation, int* out);

	// virtual functions
	virtual bool look(Rotation rotation);			// returns true if the robot is

	virtual void turn(Direction direction);
	virtual void turn(Rotation rotation);

	virtual bool driveForward();
};

#endif
