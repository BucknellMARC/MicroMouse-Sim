#ifndef MAZE_ALGORITHM_H
#define MAZE_ALGORITHM_H

#include "define.h"
#include "MazeMap.h"

//
// flood fill algorithm
//

#define FF_BAD -1

// objects
typedef MazeArray FFMap;
typedef MazeArrayPtr FFMapPtr;

// functions
void ff_compute(MazeMap* mm, FFMapPtr in);
Direction ff_suggest(Point pos, MazeMap* mazeMap, FFMapPtr ffMap);


#endif
