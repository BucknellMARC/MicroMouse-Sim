#ifndef MAZE_ALGORITHM_C
#define MAZE_ALGORITHM_C

#include <stdio.h>
#include <string.h>

#include "define.h"
#include "FloodFill.h"
#include "MazeMap.h"

#define FF_Q_SIZE 256
Point queue[FF_Q_SIZE];
int q_start = 0;
int q_end = 0;

BOOL ff_enqueue(Point p)
{
	// make sure we aren't overwriting values in the queue
	if ((q_end + 1) - q_start == FF_Q_SIZE) {
		return FALSE;
	}

	queue[++q_end % FF_Q_SIZE] = p;
}

Point ff_dequeue()
{
	// return null value if the queue is empty
	if (q_start == q_end) {
		Point p;
		p.x = -1;
		p.y = -1;
		return p;
	}

	return queue[++q_start % FF_Q_SIZE];
}

// computes the flood fill for the first time (center is the target)
void ff_compute(MazeMap* mm, FFMapPtr in)
{
	// make sure flood fill map has been properly initialized
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			in[row][col] = FF_BAD;
		}
	}

	// current point starts at given node
	Point current;
	current.x = MAZE_WIDTH / 2;
	current.y = MAZE_HEIGHT / 2;
	in[current.y][current.x] = 0;

	// keep dequeuing until there is no more left
	for(; current.x > -1; current = ff_dequeue()) {

		int curDistance = in[current.y][current.x];

		// investigate the neighbors
		BOOL northWall = mm_is_wall(mm, current, NORTH);
		BOOL eastWall = mm_is_wall(mm, current, EAST);
		BOOL southWall = mm_is_wall(mm, current, SOUTH);
		BOOL westWall = mm_is_wall(mm, current, WEST);

		// add point to queue if there is no wall
		Point p;
		if (!northWall) {
			p.x = current.x; p.y = current.y + 1;

			// only add if the value is currently bad
			if (in[p.y][p.x] == FF_BAD) {
				in[p.y][p.x] = curDistance + 1;

				ff_enqueue(p);
			}
		}
		if (!eastWall) {
			p.x = current.x + 1; p.y = current.y;
			
			// only add if the value is currently bad
			if (in[p.y][p.x] == FF_BAD) {
				in[p.y][p.x] = curDistance + 1;

				ff_enqueue(p);
			}
		}
		if (!southWall) {
			p.x = current.x; p.y = current.y - 1;

			// only add if the value is currently bad
			if (in[p.y][p.x] == FF_BAD) {
				in[p.y][p.x] = curDistance + 1;

				ff_enqueue(p);
			}

		}
		if (!westWall) {
			p.x = current.x - 1; p.y = current.y;
			
			// only add if the value is currently bad
			if (in[p.y][p.x] == FF_BAD) {
				in[p.y][p.x] = curDistance + 1;

				ff_enqueue(p);
			}
		}
	}
}

// retargets the flood fill map
// ** UNTESTED **	-- this will be wrong with the middle zero blocks
void ff_recompute_target(int targetX, int targetY, FFMapPtr in)
{
	// find the current target
	int currentX = FF_BAD;
	int currentY = FF_BAD;
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			int value = in[row][col];

			if (value == 0) {
				currentX = col;
				currentY = row;

				break;
			}
		}

		// if inner forloop found a match, break out of this one
		if (currentX != FF_BAD) {
			break;
		}
	}

	// the new difference will be the current value of the new target
	int difference = in[currentY][currentX];

	// displace the rest of the array
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {

			// make sure the value is always positive
			int curValue = in[row][col];
			if (difference > curValue) {
				in[row][col] = difference - curValue;
			}
			else {
				in[row][col] = curValue - difference;
			}
		}
	}
}

// uses floodfill to determine where to go
Direction ff_suggest(Point pos, MazeMap *mazeMap, FFMapPtr ffMap)
{
	int minVal =  100000;
	Direction minDir = EAST;

	BOOL eastWall = mm_is_wall(mazeMap, pos, EAST);
	BOOL southWall = mm_is_wall(mazeMap, pos, SOUTH);
	BOOL westWall = mm_is_wall(mazeMap, pos, WEST);
	BOOL northWall = mm_is_wall(mazeMap, pos, NORTH);

	int eastVal = 10000; int southVal = 10000; int westVal = 10000; int northVal = 10000;
	if (!eastWall) {
		eastVal = ffMap[pos.y][pos.x + 1];
	}
	if (!southWall) {
		southVal = ffMap[pos.y - 1][pos.x];
	}
	if (!westWall) {
		westVal = ffMap[pos.y][pos.x - 1];
	}
	if (!northWall) {
		northVal = ffMap[pos.y + 1][pos.x];
	}

	if (!eastWall && eastVal < minVal) {
		minDir = EAST;
		minVal = eastVal;
	}
	if (!southWall && southVal < minVal) {
		minDir = SOUTH;
		minVal = southVal;
	}
	if (!westWall&& westVal < minVal) {
		minDir = WEST;
		minVal = westVal;
	}
	if (!northWall && northVal < minVal) {
		minDir = NORTH;
	}

	return minDir;
}

#endif
