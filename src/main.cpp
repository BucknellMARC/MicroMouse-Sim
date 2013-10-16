#include <stdio.h>
#include <GL/glut.h>

#include "define.h"
#include "VirtualMaze.h"

void renderScene();

VirtualMaze* firstMaze;
Rectangle* firstRectangle;

int main(int argc, char** argv) {
	printf("Initializing glut...\n");

	// run preliminary init
	glutInit(&argc, argv);

	// init the display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// put the window position
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// create the window
	glutCreateWindow("My First GLUT");

	firstMaze = new VirtualMaze();
	//firstRectangle = new Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// send the rendering loop to GLUT
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 1;
}

void renderScene() {
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	firstMaze->draw();
	//firstRectangle->draw();

	glutSwapBuffers();
}
