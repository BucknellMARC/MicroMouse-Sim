#ifndef EXPLORE_H
#define EXPLORE_H

#include "MazeMap.h"

typedef struct {
	MazeMap mazeMap;

	BOOL returning;
	MazeArray exHistory;

	int prevTravelPos;
	Direction prevTravel[512];
} ExploreModule;

#define SEARCH_EXPLORED	4

// functions
ExploreModule explore_create();
Direction explore_suggest(Point pos, Direction curDirection, ExploreModule* em);

#endif
