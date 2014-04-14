#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

#include "define.h"

// holds the state of the wall
typedef enum {
	WALL = 1,
	NOWALL = 0,
	UNKNOWN = -1
} WallState;

typedef struct {
	WallState horizWalls[MAZE_HEIGHT - 1][MAZE_WIDTH];
	WallState vertWalls[MAZE_HEIGHT][MAZE_WIDTH - 1];

} MazeMap;

// constructor
MazeMap mm_create();

//
// main methods
//

BOOL mm_is_wall(MazeMap* mazeMap, Point pos, Direction direction);
BOOL mm_is_wall_r(MazeMap* mazeMap, Point pos, Direction direction, Rotation rotation);
void mm_set_wall(MazeMap* mazeMap, BOOL state, Point pos, Direction direction);

BOOL mm_get_look_position(Point pos, Direction direction, int* xLook, int* yLook);
void mm_one_ahead_direction(Direction direction, Point* pos);

//
// helper methods
//

Direction rotation_to_direction(Direction curDirection, Rotation rotation);
Rotation direction_to_rotation(Direction curDirection, Direction targetDirection);

#endif
