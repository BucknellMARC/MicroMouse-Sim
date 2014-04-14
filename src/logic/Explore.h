#ifndef EXPLORE_H
#define EXPLORE_H

#include "FloodFill.h"

typedef struct {
	BOOL returning;
	MazeArray exHistory;

	int prevTravelPos;
	Direction prevTravel[512];
} ExploreModule;

#define SEARCH_EXPLORED	4

// functions
ExploreModule explore_create();
Direction explore_suggest(Point pos, Direction curDirection, MazeMap* mazeMap, ExploreModule* em);

#endif
