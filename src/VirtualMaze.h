#ifndef MAZE_H
#define MAZE_H

#include <vector>
using namespace std;

#include "define.h"
#include "Rectangle.h"

class VirtualMaze {
private:
	//
	// class members
	//

	bool** horizontalWalls;
	bool** verticalWalls;

	vector<Rectangle> walls;

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

	//
	// static methods
	//

	static int getBlockWidthPX();
};

#endif
