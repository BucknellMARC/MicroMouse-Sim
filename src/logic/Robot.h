#ifndef ROBOT_H
#define ROBOT_H

#include "define.h"
#include "MazeMap.h"
#include "MazeAlgorithm.h"

typedef struct {
	// position and direction the robot is facing
	int xPos, yPos;
	Direction direction;
	BOOL isExploring;

	FFMap ffMap;

	MazeMap mazeMap;
} Robot;

// constructor
Robot robot_create(int xPos, int yPos);

// movement algorithms
void robot_run(Robot* robot);
void robot_run_flood_fill(Robot* robot);

void robot_turn_d(Robot* robot, Direction direction);
void robot_turn_r(Robot* robot, Rotation rotation);

BOOL robot_drive_forward(Robot* robot);

#endif
