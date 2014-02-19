#ifndef ROBOT_H
#define ROBOT_H

#include "define.h"
#include "MazeMap.h"
#include "MazeAlgorithm.h"

typedef struct {
	// position and direction the robot is facing
	int xPos, yPos;
	Direction direction;

	MazeArray posHistory[MAZE_HEIGHT][MAZE_WIDTH];
	FFMapPtr ffMap;

	MazeMap* mazeMap;
} Robot;

// constructor
Robot* robot_create(int xPos, int yPos, MazeMap* mm);

// movement algorithms
void robot_run_right_wall(Robot* robot);
void robot_run_flood_fill(Robot* robot);

// rotation assists
Direction	robot_rotation_to_direction(Robot* robot, Rotation rotation);
//BOOL		robot_rotationToCoords(Robot* robot, Rotation rotation, int* out);

// interfacing
BOOL robot_look(Robot* robot, Rotation rotation);			// returns TRUE if the robot can move to that position

void robot_turn_d(Robot* robot, Direction direction);
void robot_turn_r(Robot* robot, Rotation rotation);

BOOL robot_drive_forward(Robot* robot);

// deconstructor
void robot_destroy(Robot* robot);

#endif
