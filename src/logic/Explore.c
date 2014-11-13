#ifndef EXPLORE_C
#define EXPLORE_C

#include <stdio.h>

#include "MazeMap.h"

#include "Explore.h"

Direction explore_return(ExploreModule* em);		// pops em->prevTravel and returns the opposite direction

ExploreModule explore_create()
{
	// init the module
	ExploreModule em;

	em.mazeMap = mm_create();

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

Direction explore_suggest(Point pos, Direction curDirection, ExploreModule* em)
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
	BOOL northWall = mm_is_wall(&em->mazeMap, pos, NORTH) || pos.y >= (MAZE_HEIGHT - 1);
	BOOL eastWall = mm_is_wall(&em->mazeMap, pos, EAST) || pos.x >= (MAZE_WIDTH- 1);
	BOOL southWall = mm_is_wall(&em->mazeMap, pos, SOUTH) || pos.y <= 0;
	BOOL westWall = mm_is_wall(&em->mazeMap, pos, WEST) || pos.x <= 0;

  BOOL northAvailable = (!northWall) && (!em->exHistory[pos.y+1][pos.x]);
  BOOL eastAvailable = !eastWall && !em->exHistory[pos.y][pos.x+1];
  BOOL southAvailable = !southWall && !em->exHistory[pos.y-1][pos.x];
  BOOL westAvailable = !westWall && !em->exHistory[pos.y][pos.x-1];
	BOOL canProceed = northAvailable || eastAvailable || southAvailable || westAvailable;

	Direction toGo;

	// if there is only one way to go, return
	if (!canProceed) {
		em->returning = TRUE;
		return explore_return(em);
	}

  if (northAvailable) {
    toGo = NORTH;
  } else if (eastAvailable) {
    toGo = EAST;
  } else if (southAvailable) {
    toGo = SOUTH;
  } else if (westAvailable) {
    toGo = WEST;
  } else {
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
