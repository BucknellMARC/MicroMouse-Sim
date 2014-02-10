#ifndef ROBOT_H
#define ROBOT_H

#include "define.h"
#include "MazeMap.h"
#include "MazeAlgorithm.h"

typedef struct {
	// position and direction the robot is facing
	int xPos, yPos;
	Direction direction;

	int posHistory[MAZE_HEIGHT][MAZE_WIDTH];
	ff_map map;

	MazeMap* mazeMap;
} Robot;

// constructor
Robot* robot_create(int xPos, int yPos, MazeMap *mm);

// movement algorithms
void robot_runRightWall(Robot* robot);
void robot_runFloodFill(Robot* robot);

// rotation assists
Direction	robot_rotationToDirection(Robot* robot, Rotation rotation);
//bool		robot_rotationToCoords(Robot* robot, Rotation rotation, int* out);

// interfacing
bool robot_look(Robot* robot, Rotation rotation);			// returns true if the robot can move to that position

void robot_turn(Robot* robot, Direction direction);
void robot_turn(Robot* robot, Rotation rotation);

bool robot_driveForward(Robot* robot);

// deconstructor
void robot_destroy(Robot* robot);

#endif
