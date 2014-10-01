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

extern "C" {
	#include "logic/MazeMap.h"
     #include "logic/FloodFill.h"
}

#include "Rectangle.h"
#include "Circle.h"

// GLUT font we will be using
#define FFD_TEXT GLUT_BITMAP_9_BY_15

typedef struct {
	Rectangle rectangle;
	int row, col;
	BOOL isHorizontal;
} Wall;

class VirtualMaze {
private:
	//
	// class members
	//

	MazeMap mazeMap;
	MazeMap* robotMazeMap;

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

        VirtualMaze(int seed=-1);

	//
	// main methods
	//

	void draw();

	void bindRobotMap(MazeMap* robotMazeMap);

	//
	// getters
	//

	MazeMap* getMazeMap();

	~VirtualMaze();

	//
	// private methods
	//
private:

	// maze generation algorithms
	void primGeneration(int seed);

	//
	// static methods
	//
public:

     static void drawFloodFill(FFMapPtr source);

	static int getBlockWidthPX();
     static void sspaceToPspace(float *x, float *y);
};

//
// Display Methods
//

#endif
