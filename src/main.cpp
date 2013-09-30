#include <cstdio>
#include <GL/glut.h>

void renderScene();

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

	// send the rendering loop to GLUT
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 1;
}

void renderScene() {
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// draw the triangle
	glBegin(GL_TRIANGLES);
			glVertex3f(-0.5,-0.5,0.0);
			glVertex3f(0.5,0.0,0.0);
			glVertex3f(0.0,0.5,0.0);
	glEnd();

	glutSwapBuffers();
}
