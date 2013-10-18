#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

enum WallState {
	WALL,
	FREE,
	UNKNOWN
};

class MazeMap {
protected:
	//
	// main members
	//

	WallState** horizontalWalls;
	WallState** verticalWalls;

public:
	//
	// constructors
	//

	MazeMap();

	//
	// main methods
	//


};

#endif
