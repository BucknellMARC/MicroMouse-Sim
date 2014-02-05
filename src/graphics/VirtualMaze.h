#ifndef VIRTUALMAZE_H
#define VIRTUALMAZE_H

/*
 * Contains a way to visualize what the robot sees when searching
 * through the maze.  It will be able to differentiate between
 * walls the robot does and doesn't know about
 */

#include <vector>
using namespace std;

#include "define.h"
#include "MazeMap.h"
#include "Rectangle.h"
#include "Circle.h"

class VirtualMaze {
private:
	//
	// class members
	//

	MazeMap* mazeMap;

	vector<Rectangle> walls;
	Circle** circles;

	//
	// static members
	//

	static const int blockWidthPX = SCREEN_WIDTH / MAZE_WIDTH;
	static const int wallWidthPX = 5;

public:
	//
	// constructors
	//

	VirtualMaze();

	//
	// main methods
	//

	void draw();
	void rebuildWalls();

	MazeMap* getMazeMap();

	~VirtualMaze();

	//
	// private methods
	//
private:

	// maze generation algorithms
	void primGeneration();

	//
	// static methods
	//
public:

	static int getBlockWidthPX();
};

#endif