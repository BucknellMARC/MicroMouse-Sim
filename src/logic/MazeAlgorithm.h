#ifndef MAZE_ALGORITHM_H
#define MAZE_ALGORITHM_H

#include "define.h"
#include "MazeMap.h"
#include "Robot.h"

typedef struct {
	int array[MAZE_HEIGHT][MAZE_WIDTH];
} ff_map;

#define MALGO_FF_BAD -1

// flood fill algorithms
void malgo_floodfill_compute(MazeMap *mm, ff_map *in);
void malgo_floodfill_recompute_target(int targetX, int targetY, ff_map *in);
void malgo_floodfill_make_move(int xPos, int yPos, ff_map *map);

#endif
