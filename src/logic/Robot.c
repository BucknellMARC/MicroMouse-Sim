#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "define.h"
#include "Robot.h"
#include "Explore.h"
#include "FloodFill.h"

// default initializer
Robot robot_create(int xPos, int yPos)
{
	// declare a robot on the stack and zero it out
	Robot robot;
	memset(&robot, 0, sizeof(Robot));

	// assign the initial position to the robot
	Point pos = { xPos, yPos };
	robot.pos = pos;
	robot.direction = EAST;
	
	// the robot will always start out exploring
	robot.isExploring = TRUE;

	// init the exploration component
	robot.em = explore_create();

	robot.distanceTraveled = 0;

	return robot;
}

void robot_run(Robot* robot) {
	// check to see if the robot has explored the whole maze
	BOOL exploredMaze = TRUE;

	// actually performed check
	MazeMap* rmm = &robot->em.mazeMap;
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
	
		ff_compute(&robot->em.mazeMap, robot->ffMap);
	}


	/// Main robot run code ///
	///////////////////////////

	// run exploration if the robot is exploring
	Direction direction;
	if (robot->isExploring) {
		direction = explore_suggest(robot->pos, robot->direction, &robot->em);
	}
	// otherwise run the flood fill algorithm
	else {
		robot_run_flood_fill(robot);
		return;
	}

	robot_turn_d(robot, direction);

	// only drive forward if there is no wall
	BOOL wallForward = mm_is_wall(&robot->em.mazeMap, robot->pos, robot->direction);
	if (!wallForward) {
		robot_drive_forward(robot);
	}
}

void robot_run_flood_fill(Robot* robot) {

	Rotation dToGo = ff_suggest(robot->pos, &robot->em.mazeMap, robot->ffMap);

	// turn that direction
	robot_turn_d(robot, dToGo);
	
	// and drive forward
	robot_drive_forward(robot);
}

void robot_turn_d(Robot* robot, Direction direction) {
	robot->direction = direction;
}

void robot_turn_r(Robot* robot, Rotation rotation) {
	robot->direction = rotation_to_direction(robot->direction, rotation);
}

BOOL robot_drive_forward(Robot* robot) {
	Direction direction = robot->direction;

	switch (direction) {
	case NORTH:
		robot->pos.y++;
		break;

	case EAST:
		robot->pos.x++;
		break;

	case SOUTH:
		robot->pos.y--;
		break;

	case WEST:
		robot->pos.x--;
		break;

	default:
		printf("Error: Robot is in an unexpected state!\n");
	}

	// increase the distance traveled
	robot->distanceTraveled++;

	return TRUE;
}

#endif

