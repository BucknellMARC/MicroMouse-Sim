#ifndef CIRCLE_H
#define CIRCLE_H

#include "define.h"

#define CIRCLE_RESOLUTION	8
#define CIRCLE_NUM_VERTS	(int)((float)CIRCLE_RESOLUTION * 1.5f + 1)

#define CIRCLE_PI 3.1415926f

class Circle {
private:
	int x, y;
	int radius;

	float* glCoordsX;
	float* glCoordsY;

public:
	//
	// Constructors
	//

	Circle(int x, int y, int radius);

	//
	// Main Functions
	//

	void draw();

	// repositioning functions
	void setPos(int x, int y);
	void translate(int x, int y);

	// resizing function
	void resize(int radius);

	//
	// Getters
	//

	int getX();
	int getY();
	int getRadius();

	//
	// Private Functions
	//
private:
	void rebuildGLCoords();
};

#endif
