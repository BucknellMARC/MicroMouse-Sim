#ifndef VIRTUALMAZE_CPP
#define VIRTUALMAZE_CPP

/*
 * VirtualMaze is used to render the maze on screen it
 * contains Rectangles that draw walls and inherits
 * MazeMap which is what the robot will use to keep
 * track of where it is
 */

#include <errno.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
using namespace std;


#include "define.h"
#include "Rectangle.h"

extern "C" {
	#include "logic/MazeMap.h"
     #include "logic/FloodFill.h"
}

#include "VirtualMaze.h"
//
// constructors
//

VirtualMaze::VirtualMaze(int seed) {
	mazeMap = mm_create();
        
        if(seed==-1){
                // seed is just going to be the current time
	        seed = time(NULL);
        }
        
	// perform prim generation
	primGeneration(seed);

	// init the circle memory
	circles = new Circle*[MAZE_WIDTH * MAZE_HEIGHT];
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for (int col = 0; col < MAZE_HEIGHT; col++) {
			int arrayPos = row * MAZE_WIDTH + col;
			circles[arrayPos] = new Circle(row * blockWidthPX, col * blockWidthPX, wallWidthPX/2);
		}
	}
}

VirtualMaze::VirtualMaze(char *filename) {
    FILE *fhandle = fopen(filename, "r");
    if (fhandle == NULL) {
        perror("Could not open file");
        throw strerror(errno);
    }
    // Use the first line to figure out how wide the maze is
    char buffer[512];
    fgets(buffer, 512, fhandle);
    int width = strlen(buffer);
    printf("Maze width: %i\n",width);
    if(width/2 != MAZE_WIDTH) {
        printf("Warning: Maze file width is wrong!\n");
    }
    MazeMap map = mm_create();
    for(int y=0; y<MAZE_HEIGHT; y++) {
        fgets(buffer, 512, fhandle);
        printf("V: %s", buffer);
        for(int x=0; x < MAZE_WIDTH*2; x++) {
            mazeMap.vertWalls[y][x] = (buffer[2*x+2] == *"*"?WALL:NOWALL);
        }
        fgets(buffer, 512, fhandle);
        printf("H: %s", buffer);
        for(int x=0; x < 512 && buffer[x] != *"\n"; x++) {
                mazeMap.horizWalls[y][x] = (buffer[2*x+1] == *"*"?WALL:NOWALL);
        }
    }
    printf("Done read!\n");

    // init the circle memory
	circles = new Circle*[MAZE_WIDTH * MAZE_HEIGHT];
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for (int col = 0; col < MAZE_HEIGHT; col++) {
			int arrayPos = row * MAZE_WIDTH + col;
			circles[arrayPos] = new Circle(row * blockWidthPX, col * blockWidthPX, wallWidthPX/2);
		}
	}
        printf("Done circles!\n");
}

//
// main methods
//

// draws the maze
void VirtualMaze::draw() {

	// set the draw color to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// build the rows
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int column = 0; column < (MAZE_WIDTH - 1); column++) {
			if (mazeMap.vertWalls[row][column] == WALL) {
				int x = (column+1) * blockWidthPX - wallWidthPX / 2;
				int y = row * blockWidthPX;

				// init a rectangle
				Rectangle rectangle(x, y, wallWidthPX, blockWidthPX);

				if (robotMazeMap->vertWalls[row][column] == UNKNOWN) {
					rectangle.draw(0.25f, 0.25f, 0.25f);
				}
				else {
					rectangle.draw(1.0f, 1.0f, 1.0f);
				}
			}
		}
	}

	// build the columns
	for (int row = 0; row < (MAZE_HEIGHT - 1); row++) {
		for (int column = 0; column < MAZE_WIDTH; column++) {
			if (mazeMap.horizWalls[row][column] == WALL) {
				int x = column * blockWidthPX;
				int y = (row+1) * blockWidthPX - wallWidthPX / 2;

				// init a rectangle
				Rectangle rectangle(x, y, blockWidthPX, wallWidthPX);
				rectangle.draw(0.25f, 0.25f, 0.25f);

				if (robotMazeMap->horizWalls[row][column] == UNKNOWN) {
					rectangle.draw(0.25f, 0.25f, 0.25f);
				}
				else {
					rectangle.draw(1.0f, 1.0f, 1.0f);
				}
			}
		}
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	// draw every circle
	for (int n = 0; n < (MAZE_WIDTH * MAZE_HEIGHT); n++) {
		circles[n]->draw();
	}
}

void VirtualMaze::bindRobotMap(MazeMap* robotMazeMap)
{
	this->robotMazeMap = robotMazeMap;
}

MazeMap* VirtualMaze::getMazeMap() {
	return &mazeMap;
}

VirtualMaze::~VirtualMaze() {
}

//
// Private Methods
//

// prim's algorithm
void VirtualMaze::primGeneration(int seed) {
	// init the random number generator the
	
	srand(seed);

	printf("Starting prim generation...");

	// put in all the walls
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < (MAZE_WIDTH - 1); col++) {
			mazeMap.vertWalls[row][col] = WALL;
		}
	}
	for (int row = 0; row < (MAZE_HEIGHT - 1); row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			mazeMap.horizWalls[row][col] = WALL;
		}
	}

	// init variable that keeps track of whether or not square is part of the maze
	BOOL partOfMaze[MAZE_HEIGHT][MAZE_WIDTH];
	for (int row = 0; row < MAZE_HEIGHT; row++) {
		for (int col = 0; col < MAZE_WIDTH; col++) {
			partOfMaze[row][col] = FALSE;
		}
	}

	// holds list of walls active in the algorithm
	vector<Point> activeWallList;

	// add the first cell location to the active wall list
	Point zeroPoint;
	zeroPoint.x = 0;
	zeroPoint.y = 0;
	activeWallList.push_back(zeroPoint);

	// loop until the active wall list is zero
	while (activeWallList.size() > 0) {

		// get a random location from the wall list
		int currentPos = rand() % activeWallList.size();
		Point current = activeWallList[currentPos];

		// lists the direction that the active spot can go in...
		vector<Direction> canGo;

		// figure out what is part of the maze and what is not
		if (current.y < (MAZE_HEIGHT - 1) && !partOfMaze[current.y + 1][current.x]) {
			canGo.push_back(NORTH);
		}
		if (current.x < (MAZE_WIDTH - 1) && !partOfMaze[current.y][current.x + 1]) {
			canGo.push_back(EAST);
		}
		if (current.y > 0 && !partOfMaze[current.y - 1][current.x]) {
			canGo.push_back(SOUTH);
		}
		if (current.x > 0 && !partOfMaze[current.y][current.x - 1]) {
			canGo.push_back(WEST);
		}

		// the DOF is just number of directions you can go
		int degreesOfFreedom = canGo.size();

		// if the degrees of freedom zero, then remove it from the list
		if (degreesOfFreedom == 0) {
			activeWallList.erase(activeWallList.begin() + currentPos);
		}
		else {
			// go in a random direction
			Direction direction = canGo[rand() % canGo.size()];

			// break down the wall between the two locations
			mm_set_wall(&mazeMap, NOWALL, current, direction);

			// get the new destination
			Point destination = current;
			switch (direction) {
			case NORTH:
				destination.y++;
				break;
			case EAST:
				destination.x++;
				break;
			case SOUTH:
				destination.y--;
				break;
			case WEST:
				destination.x--;
				break;
			}

			// make the destination part of the maze
			partOfMaze[destination.y][destination.x] = TRUE;

			// add it to the wall lsit
			activeWallList.push_back(destination);
		}
	}

	// create empty center space
	Point oneBack = { MAZE_WIDTH / 2 - 1, MAZE_HEIGHT / 2 - 1 };
	Point middle = { oneBack.x + 1, oneBack.y + 1 };
	mm_set_wall(&mazeMap, FALSE, oneBack, NORTH);
	mm_set_wall(&mazeMap, FALSE, oneBack, EAST);
	mm_set_wall(&mazeMap, FALSE, middle, SOUTH);
	mm_set_wall(&mazeMap, FALSE, middle, WEST);


        printf("done!\n");
}

//
// static methods
//

void VirtualMaze::drawFloodFill(FFMapPtr source)
{
     for (int row = 0; row < MAZE_WIDTH; row++) {
          for (int col = 0; col < MAZE_HEIGHT; col++) {
               int val = source[row][col];

               // convert the value to text
               char charsToPrint[10];
               sprintf(charsToPrint, "%d", val);

               // move the bitmap drawer to the right location
               float x = ((float)col + 0.4f) * MAZE_WIDTH_PX;
               float y = ((float)row + 0.4f) * MAZE_HEIGHT_PX;
               VirtualMaze::sspaceToPspace(&x, &y);
               glRasterPos2f(x, y);

               // draw the text
               for (int n = 0; n < 10; n++) {
                    char c = charsToPrint[n];

                    if (c == 0) {
                         break;
                    }

                    glutBitmapCharacter(FFD_TEXT, c);
               }
          }
     }
}

int VirtualMaze::getBlockWidthPX() {
	return blockWidthPX;
}

void VirtualMaze::sspaceToPspace(float *x, float *y)
{
     int xVal = *x;
     *x = 2.0 * xVal / (float)SCREEN_WIDTH - 1.0f;

     int yVal = *y;
     *y = 2.0 * yVal / (float)SCREEN_HEIGHT - 1.0f;
}

#endif
