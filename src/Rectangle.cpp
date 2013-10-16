#ifndef RECTANGLE_CPP
#define RECTANGLE_CPP

#include <stdio.h>
#include <GL/gl.h>

#include "define.h"
#include "Rectangle.h"

// default constructor
Rectangle::Rectangle() {
	// use normal constructor but set everything to zero
	Rectangle(0, 0, 0, 0);
}

// main constructor
Rectangle::Rectangle(int x, int y, int width, int height) {
	// set the position
	this->x = x;
	this->y = y;

	// set dimensions
	this->width = width;
	this->height = height;

	rebuildGLCoords();
}

void Rectangle::draw() {
	glBegin(GL_TRIANGLES);
		// first triangle
		glVertex3f(glCoordsX, glCoordsY, 0.0f);
		glVertex3f(glCoordsX + glCoordsWidth, glCoordsY, 0.0f);
		glVertex3f(glCoordsX + glCoordsWidth, glCoordsY + glCoordsHeight, 0.0f);

		// second triangle
		glVertex3f(glCoordsX + glCoordsWidth, glCoordsY + glCoordsHeight, 0.0f);
		glVertex3f(glCoordsX, glCoordsY + glCoordsHeight, 0.0f);
		glVertex3f(glCoordsX, glCoordsY, 0.0f);
	glEnd();
}

void Rectangle::setPos(int x, int y) {
	this->x = x;
	this->y = y;

	// rebuild opengl coords
	rebuildGLCoords();
}

void Rectangle::translate(int x, int y) {
	this->x += x;
	this->y += y;

	// rebuild opengl coords
	rebuildGLCoords();
}

void Rectangle::resize(int width, int height) {
	this->width = width;
	this->height = height;

	// rebuild opengl coords
	rebuildGLCoords();
}

int Rectangle::getX() {
	return x;
}

int Rectangle::getY() {
	return y;
}

int Rectangle::getWidth() {
	return width;
}

int Rectangle::getHeight() {
	return height;
}

void Rectangle::rebuildGLCoords() {
	// convert X and Y coords to GL screen space
	glCoordsX = 2.0 * (float)x / (float)SCREEN_WIDTH - 1.0f;
	glCoordsY = 2.0 * (float)y / (float)SCREEN_HEIGHT - 1.0f;

	// convert width and height to GL screen space
	glCoordsWidth = 2.0 * (float)width / (float)SCREEN_WIDTH;
	glCoordsHeight = 2.0 * (float)height / (float)SCREEN_HEIGHT;
}

#endif
