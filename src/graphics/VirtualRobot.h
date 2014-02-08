#ifndef VIRTUALROBOT_H
#define VIRTUALROBOT_H

#include "define.h"

#include "logic/Robot.h"
#include "logic/MazeAlgorithm.h"
#include "VirtualMaze.h"

class VirtualRobot {
private:
	Robot* robot;
	Rectangle* rectangle;
	VirtualMaze* virtualMaze;

	ff_map floodFillMap;

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

	//
	// getters
	//

	ff_map *getFloodFillMap();

	// deconstructor
	~VirtualRobot();
};

#endif
