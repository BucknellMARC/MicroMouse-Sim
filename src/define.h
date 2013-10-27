// contains all preprocessor definitions

#ifndef DEFINE_H
#define DEFINE_H

// screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

// maze dimensions
#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16

// meaning of direction
enum Direction {
	EAST,
	SOUTH,
	WEST,
	NORTH
};

// meaning of rotation
enum Rotation {
	FORWARDS,
	LEFT,
	RIGHT,
	BACKWARDS
};

// 2 dimensional point
struct Point {
	int x;
	int y;
};

//
// Functions
//

void pixelPointToGLPoint(float x, float y, float* outX, float* outY);
void pixelDimToGLDim(float width, float height, float* outWidth, float* outHeight);

#endif
