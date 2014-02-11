#ifndef MAZE_ALGORITHM_H
#define MAZE_ALGORITHM_H

#include "define.h"
#include "MazeMap.h"

//typedef struct {
//	int array[MAZE_HEIGHT][MAZE_WIDTH];
//} ff_map;

typedef MazeArray FFMap;
typedef MazeArrayPtr FFMapPtr;

#define MALGO_FF_BAD -1

// flood fill algorithms
void malgo_floodfill_compute(MazeMap* mm, FFMapPtr in);
void malgo_floodfill_recompute_target(int targetX, int targetY, FFMapPtr in);
Direction malgo_floodfill_suggest(int xPos, int yPos, MazeMap* mazeMap, FFMapPtr ffMap);

#endif
