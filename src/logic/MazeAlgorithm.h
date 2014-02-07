#ifndef MAZE_ALGORITHM_H
#define MAZE_ALGORITHM_H

#include "define.h"
#include "MazeMap.h"
#include "Robot.h"

typedef int[MAZE_HEIGHT][MAZE_WIDTH] ff_map;

// flood fill algorithms
void malgo_floodfill_compute(int targetX, targetY, MazeMap *mm, ff_map *in);
void malgo_floodfill_recompute_target(int targetX, int targetY, ff_map *in);
void malgo_floodfill_make_move(int xPos, int yPos, ff_map *map);

#endif
