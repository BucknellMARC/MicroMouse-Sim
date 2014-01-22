#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

#include "define.h"

class MazeMap {
protected:
	//
	// main members
	//

	bool horizWalls[MAZE_HEIGHT - 1][MAZE_WIDTH];
	bool vertWalls[MAZE_HEIGHT][MAZE_WIDTH - 1];

public:
	//
	// constructors
	//

	MazeMap();

	//
	// main methods
	//

	bool doesWallExist(int x, int y, Direction direction);

	void setWall(bool state, int x, int y, Direction direction);

protected:
	bool getLookPositions(int x, int y, Direction direction, int* xLook, int* yLook);
};

#endif
