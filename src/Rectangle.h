#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
	int x, y;
	int width, height;

public:
	Rectangle(int x, int y, int width, int height);

	// drawing function
	void draw();

	// getter functions
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};

#endif
