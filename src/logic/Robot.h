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
Robot* robot_create(int xPos, int yPos, MazeMap* mm);

// movement algorithms
void robot_run_right_wall(Robot* robot);
void robot_run_flood_fill(Robot* robot);

// rotation assists
Direction	robot_rotation_to_direction(Robot* robot, Rotation rotation);
//bool		robot_rotationToCoords(Robot* robot, Rotation rotation, int* out);

// interfacing
bool robot_look(Robot* robot, Rotation rotation);			// returns true if the robot can move to that position

void robot_turn(Robot* robot, Direction direction);
void robot_turn(Robot* robot, Rotation rotation);

bool robot_drive_forward(Robot* robot);

// deconstructor
void robot_destroy(Robot* robot);

#endif
