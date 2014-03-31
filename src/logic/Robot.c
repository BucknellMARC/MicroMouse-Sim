#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "define.h"
#include "Robot.h"
#include "MazeAlgorithm.h"

// default initializer
Robot robot_create(int xPos, int yPos)
{
	// declare a robot on the stack and zero it out
	Robot robot;
	memset(&robot, 0, sizeof(Robot));

	// assign the initial position to the robot
	robot.xPos = xPos;
	robot.yPos = yPos;
	robot.direction = EAST;
	
	// the robot will always start out exploring
	robot.isExploring = TRUE;

	// zero out pos history
	memset(robot.posHistory, 0, sizeof(MazeArray));

	// create an empty mazemap
	robot.mazeMap = mazemap_create();

	return robot;
}

void robot_run(Robot* robot) {
	// check to see if the robot has explored the whole maze
	BOOL exploredMaze = TRUE;

	// actually performed check
	MazeMap* rmm = &robot->mazeMap;
	for (int row = 0; row < MAZE_HEIGHT - 1; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			if (rmm->horizWalls[row][col] == UNKNOWN) {
				exploredMaze = FALSE;
			}
		}
	}
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH - 1; col++) {
			if (rmm->vertWalls[row][col] == UNKNOWN) {
				exploredMaze = FALSE;
			}
		}
	}

	// if the maze has been fully explored, calculate the flood fill map and set the flag
	if (robot->isExploring && exploredMaze) {
		robot->isExploring = FALSE;
	
		malgo_floodfill_compute(&robot->mazeMap, robot->ffMap);
	}


	/// Main robot run code ///
	///////////////////////////

	// run exploration if the robot is exploring
	Direction direction;
	if (robot->isExploring) {
		direction = malgo_explore_suggest(
			robot->xPos, robot->yPos, robot->direction, &robot->mazeMap, robot->posHistory
			);
	}
	// otherwise run the flood fill algorithm
	else {
		robot_run_flood_fill(robot);
		return;
	}

	robot_turn_d(robot, direction);

	// only drive forward if there is no wall
	BOOL wallForward = mazemap_does_wall_exist(&robot->mazeMap, robot->xPos, robot->yPos, robot->direction);
	if (!wallForward) {
		robot_drive_forward(robot);

		// increment the position history
		robot->posHistory[robot->yPos][robot->xPos]++;
	}
}

void robot_run_flood_fill(Robot* robot) {

	Rotation dToGo = malgo_floodfill_suggest(robot->xPos, robot->yPos, &robot->mazeMap, robot->ffMap);

	// turn that direction
	robot_turn_d(robot, dToGo);
	
	// and drive forward
	robot_drive_forward(robot);
}

void robot_turn_d(Robot* robot, Direction direction) {
	robot->direction = direction;
}

void robot_turn_r(Robot* robot, Rotation rotation) {
	// set the new direction
	//printf("Original direction: %d\n", (int)robot->direction);

	robot->direction = mazemap_rotation_to_direction(robot->direction, rotation);

	//printf("New Direction: %d\n\n", (int)robot->direction);
}

BOOL robot_drive_forward(Robot* robot) {
	Direction direction = robot->direction;

	switch (direction) {
	case NORTH:
		robot->yPos++;
		break;

	case EAST:
		robot->xPos++;
		break;

	case SOUTH:
		robot->yPos--;
		break;

	case WEST:
		robot->xPos--;
		break;

	default:
		printf("Error: Robot is in an unexpected state!\n");
	}

	return TRUE;
}

#endif

