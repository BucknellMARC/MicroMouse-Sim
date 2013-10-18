#include <stdio.h>
#include <GL/glut.h>

#include "define.h"
#include "VirtualMaze.h"

void initWindow(int* argc, char** argv);
void startRenderLoop();
void renderScene();

VirtualMaze* firstMaze;

int main(int argc, char** argv) {
	// initialize glut
	initWindow(&argc, argv);

	//
	// init program data here
	//

	firstMaze = new VirtualMaze();

	// start the main loop
	startRenderLoop();

	return 1;
}

// initializes glut and opens up the rendering window
void initWindow(int* argc, char** argv) {
	printf("Initializing glut...\n");

	// run preliminary init
	glutInit(argc, argv);

	// init the display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// put the window position
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// create the window
	glutCreateWindow("My First GLUT");
}

// starts the rendering loop which will draw the simulation
void startRenderLoop() {
	// send the rendering loop to GLUT and start the main loop
	glutDisplayFunc(renderScene);
	glutMainLoop();
}

// the rendering loop
void renderScene() {
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	firstMaze->draw();

	glutSwapBuffers();
}
