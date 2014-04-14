#ifndef EXPLORE_C
#define EXPLORE_C

#include <stdio.h>

#include "Explore.h"

Direction explore_return(ExploreModule* em);		// pops em->prevTravel and returns the opposite direction

ExploreModule explore_create()
{
	// init the module
	ExploreModule em;

	// zero out the search array
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for(int col = 0; col < MAZE_HEIGHT; col++) {
			em.exHistory[row][col] = FALSE;
		}
	}

	em.returning = FALSE;
	em.prevTravelPos = -1;

	return em;
}

Direction explore_suggest(Point pos, Direction curDirection, MazeMap* mazeMap, ExploreModule* em)
{
	// stack up positions that have multiple options to go
	// pop off only if we have traversed all locations.
	// When we hit a dead end, pop return values off stack
	// until we reach a node that has unexplored adjacent nodes

	// mark current location as explored
	em->exHistory[pos.y][pos.x] = TRUE;

	// check for returning case
	if (em->returning) {
		return explore_return(em);
	}

	// calculate possible directions that we can travel
	BOOL northWall = mm_is_wall(mazeMap, pos, NORTH);
	BOOL eastWall = mm_is_wall(mazeMap, pos, EAST);
	BOOL southWall = mm_is_wall(mazeMap, pos, SOUTH);
	BOOL westWall = mm_is_wall(mazeMap, pos, WEST);
	int numFree = (int)(!northWall) + (int)(!eastWall) + (int)(!southWall) + (int)(!westWall);

	Direction toGo;

	// if there is only one way to go, return
	if (numFree == 1) {
		em->returning = TRUE;
		return explore_return(em);
	}

	int numSearched = 0;
	if (!northWall && pos.y < (MAZE_HEIGHT-1)) {
		if (em->exHistory[pos.y + 1][pos.x]) {
			numSearched++;
		}
		else {
			toGo = NORTH;
		}
	}
	if (!eastWall && pos.x < (MAZE_WIDTH-1)) {
		if (em->exHistory[pos.y][pos.x + 1]) {
			numSearched++;
		}
		else {
			toGo = EAST;
		}
	}
	if (!southWall && pos.y > 0) {
		if (em->exHistory[pos.y - 1][pos.x]) {
			numSearched++;
		}
		else {
			toGo = SOUTH;
		}
	}
	if (!westWall && pos.x > 0) {
		if (em->exHistory[pos.y][pos.x - 1]) {
			numSearched++;
		}
		else {
			toGo = WEST;
		}
	}

	// return if there is nowhere else to go
	if (numSearched == numFree) {
		em->returning = TRUE;
		return explore_return(em);
	}

	// save the prevous travel on the stack
	em->prevTravel[++em->prevTravelPos] = toGo;
	return toGo;
}

Direction explore_return(ExploreModule* em)
{
	if (em->prevTravelPos == -1) {
		em->returning = FALSE;
	}
	else {
		// get the opposite direction that was pushed on the stack
		Direction prevDir = em->prevTravel[em->prevTravelPos--];
		Direction returnDirection = rotation_to_direction(prevDir, BACKWARDS);

		em->returning = FALSE;

		return returnDirection;
	}
}

#endif
