#ifndef FLOOD_FILL_DISPLAY_CPP
#define FLOOD_FILL_DISPLAY_CPP

#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include "Display.h"

#define FFD_TEXT GLUT_BITMAP_9_BY_15

void display_screenspace_to_pixelspace(float *x, float *y)
{
	int xVal = *x;
	*x = 2.0 * xVal / (float)SCREEN_WIDTH - 1.0f;

	int yVal = *y;
	*y = 2.0 * yVal / (float)SCREEN_HEIGHT - 1.0f;
}

void ff_draw(ff_map *source)
{
	printf("draw_ff..\n");

	float x = 256;
	float y = 256;
	display_screenspace_to_pixelspace(&x, &y);

	glRasterPos2f(x, y);
	glutBitmapCharacter(FFD_TEXT, 'a');
}

#endif
