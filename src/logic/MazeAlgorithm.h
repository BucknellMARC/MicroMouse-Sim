#ifndef MAZE_ALGORITHM_H
#define MAZE_ALGORITHM_H

#include "define.h"
#include "MazeMap.h"

//
// flood fill algorithm
//

#define MALGO_FF_BAD -1

// objects
typedef MazeArray FFMap;
typedef MazeArrayPtr FFMapPtr;

// functions
void malgo_floodfill_compute(MazeMap* mm, FFMapPtr in);
BOOL malgo_floodfill_compute_pull_neighbor(int row, int col, Direction direction, MazeMap* mm, FFMapPtr in);
void malgo_floodfill_recompute_target(int targetX, int targetY, FFMapPtr in);
Direction malgo_floodfill_suggest(int xPos, int yPos, MazeMap* mazeMap, FFMapPtr ffMap);


// exploration algorithm

// objects
typedef struct {
	BOOL isLeftWall;
	BOOL isForwardWall;
	BOOL isRightWall;
} WallSensorInput;

// data members
extern WallSensorInput rawWalls;

// functions
Direction malgo_explore_suggest(int xPos, int yPos, Direction curDirection, MazeMap* mazeMap, MazeArrayPtr posHistory);
#endif
