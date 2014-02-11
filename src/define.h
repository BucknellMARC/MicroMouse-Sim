// contains all preprocessor definitions

#ifndef DEFINE_H
#define DEFINE_H

// screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

// maze dimensions
#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16

// dimensions in the pixel space
#define MAZE_WIDTH_PX SCREEN_WIDTH / MAZE_WIDTH
#define MAZE_HEIGHT_PX SCREEN_HEIGHT / MAZE_HEIGHT

typedef int BOOL;
#define TRUE 1
#define FALSE 0

// meaning of direction
typedef enum {
	EAST = 0,
	SOUTH = 1,
	WEST = 2,
	NORTH = 3
} Direction;

// meaning of rotation
typedef enum {
	FORWARDS,
	LEFT,
	RIGHT,
	BACKWARDS
} Rotation;

typedef int MazeArray[MAZE_HEIGHT][MAZE_WIDTH];
typedef int (*MazeArrayPtr)[MAZE_WIDTH];

#ifdef GPP
	// 2 dimensional point
	struct Point {
		int x;
		int y;
	};	
#endif

//
// Functions
//

void pixelPointToGLPoint(float x, float y, float* outX, float* outY);
void pixelDimToGLDim(float width, float height, float* outWidth, float* outHeight);

#endif
