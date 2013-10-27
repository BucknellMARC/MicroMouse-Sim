#ifndef CIRCLE_CPP
#define CIRCLE_CPP

#include <GL/gl.h>
#include <math.h>

#include "Circle.h"

//
// Constructors
//

Circle::Circle(int x, int y, int radius) {
	// set values
	this->x = x;
	this->y = y;
	this->radius = radius;

	// init the circle memory - we want the circle to be 100 tria
	this->glCoordsX = new float[CIRCLE_NUM_VERTS];
	this->glCoordsY = new float[CIRCLE_NUM_VERTS];

	// build the GL coordinates for the first time
	rebuildGLCoords();
}

//
// Main Functions
//

void Circle::draw() {
	glBegin(GL_TRIANGLE_STRIP);
		for (int n = 0; n < CIRCLE_NUM_VERTS; n++) {
			glVertex3f(glCoordsX[n], glCoordsY[n], 0.0f);
		}
	glEnd();
}

void Circle::setPos(int x, int y) {
	this->x = x;
	this->y = y;

	rebuildGLCoords();
}

void Circle::translate(int x, int y) {
	this->x += x;
	this->y += y;

	rebuildGLCoords();
}

void Circle::resize(int radius) {
	this->radius = radius;

	rebuildGLCoords();
}

//
// Getters
//

int Circle::getX() {
	return x;
}

int Circle::getY() {
	return y;
}

int Circle::getRadius() {
	return radius;
}


//
// Private Functions
//

void Circle::rebuildGLCoords() {
	// step at even lengths around the circle
	float totalRotation = 2.0f * CIRCLE_PI;
	float rotationPerStep = totalRotation / (float)CIRCLE_RESOLUTION;

	int currentPoint = 0;
	for (int n = 0; n < CIRCLE_NUM_VERTS; n++) {
		float currentRotation = currentPoint * rotationPerStep;

		float screenX = radius * sin(currentRotation) + (float)x;
		float screenY = radius * cos(currentRotation) + (float)y;
		pixelPointToGLPoint(screenX, screenY, &glCoordsX[n], &glCoordsY[n]);

		// every other node, put a center point in
		if ((currentPoint % 2) == 0) {
			n++;
			pixelPointToGLPoint((float)x, (float)y, &glCoordsX[n], &glCoordsY[n]);
		}

		// increment the current step
		currentPoint++;
	}
}

#endif
