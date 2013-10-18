#ifndef MAZEMAP_CPP
#define MAZEMAP_CPP

#include "MazeMap.h"
#include "define.h"

MazeMap::MazeMap() {
	// init the memory space for the wall states
	horizontalWalls = new WallState*[MAZE_HEIGHT + 1];
	for (int n = 0; n < (MAZE_HEIGHT + 1); n++) {
		horizontalWalls[n] = new WallState[MAZE_WIDTH];
	}

	verticalWalls = new WallState*[MAZE_HEIGHT];
	for (int n = 0; n < MAZE_HEIGHT; n++) {
		verticalWalls[n] = new WallState[MAZE_WIDTH + 1];
	}
}

#endif
