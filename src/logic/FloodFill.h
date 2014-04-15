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
void ff_compute(MazeMap* mm, FFMapPtr in);
BOOL ff_compute_pull_neighbor(int row, int col, Direction direction, MazeMap* mm, FFMapPtr in);
void ff_recompute_target(int targetX, int targetY, FFMapPtr in);
Direction ff_suggest(Point pos, MazeMap* mazeMap, FFMapPtr ffMap);


#endif
