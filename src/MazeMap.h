#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

#include "define.h"

typedef struct {
	bool horizWalls[MAZE_HEIGHT - 1][MAZE_WIDTH];
	bool vertWalls[MAZE_HEIGHT][MAZE_WIDTH - 1];

} MazeMap;

// constructor
MazeMap* mazemap_create();

//
// main methods
//

bool mazemap_doesWallExist(MazeMap* mazeMap, int x, int y, Direction direction);
void mazemap_setWall(MazeMap* mazeMap, bool state, int x, int y, Direction direction);

bool mazemap_getLookPositions(int x, int y, Direction direction, int* xLook, int* yLook);

void mazemap_destroy(MazeMap* mm);

#endif
