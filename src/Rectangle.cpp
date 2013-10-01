#include <GL/gl.h>

#include "define.h"
#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height) {
	// set the position
	this->x = x;
	this->y = y;

	// set dimensions
	this->width = width;
	this->height = height;
}

void Rectangle::draw() {
	// convert X and Y coords to GL screen space
	float glCoordsX = (float)x / (float)SCREEN_WIDTH - 1.0f;
	float glCoordsY = (float)y / (float)SCREEN_HEIGHT - 1.0f;

	// convert width and height to GL screen space
	float glCoordsWidth = (float)width / (float)SCREEN_WIDTH;
	float glCoordsHeight = (float)height / (float)SCREEN_HEIGHT;

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
