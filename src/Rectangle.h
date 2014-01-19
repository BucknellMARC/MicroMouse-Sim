#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
	int x, y;
	int width, height;

	float glCoordsX, glCoordsY;
	float glCoordsWidth, glCoordsHeight;

public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);

	//
	// main functions
	//

	void draw();
	void draw(float r, float g, float b);

	// repositioning functions
	void setPos(int x, int y);
	void translate(int x, int y);

	// resizing function
	void resize(int width, int height);

	//
	// getter functions
	//

	int getX();
	int getY();
	int getWidth();
	int getHeight();

private:
	void rebuildGLCoords();
};

#endif
