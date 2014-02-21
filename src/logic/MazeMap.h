#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

#include "define.h"

typedef struct {
	BOOL horizWalls[MAZE_HEIGHT - 1][MAZE_WIDTH];
	BOOL vertWalls[MAZE_HEIGHT][MAZE_WIDTH - 1];

} MazeMap;

// constructor
MazeMap* mazemap_create();

//
// main methods
//

BOOL mazemap_does_wall_exist(MazeMap* mazeMap, int x, int y, Direction direction);
void mazemap_set_wall(MazeMap* mazeMap, BOOL state, int x, int y, Direction direction);

BOOL mazemap_get_look_position(int x, int y, Direction direction, int* xLook, int* yLook);

void mazemap_destroy(MazeMap* mm);

//
// helper methods
//

Direction mazemap_rotation_to_direction(Direction curDirection, Rotation rotation);
Rotation mazemap_direction_to_rotation(Direction curDirection, Direction targetDirection);


#endif
