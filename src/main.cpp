#include <stdio.h>
#include <GL/glut.h>

#include "Rectangle.h"

void renderScene();

Rectangle* firstRect;

int main(int argc, char** argv) {
	printf("Initializing glut...\n");

	// run preliminary init
	glutInit(&argc, argv);

	// init the display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// put the window position
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500, 500);

	// create the window
	glutCreateWindow("My First GLUT");

	// create the rectangle
	firstRect = new Rectangle(0, 0, 10, 10);

	// send the rendering loop to GLUT
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 1;
}

void renderScene() {
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	firstRect->draw();

	glutSwapBuffers();
}
