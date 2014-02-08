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
	for (int row = 0; row < MAZE_WIDTH; row++) {
		for (int col = 0; col < MAZE_HEIGHT; col++) {
			float x = ((float)col + 0.4f) * MAZE_WIDTH_PX;
			float y = ((float)row + 0.4f) * MAZE_HEIGHT_PX;
			display_screenspace_to_pixelspace(&x, &y);

			glRasterPos2f(x, y);
			glutBitmapCharacter(FFD_TEXT, '0');
		}
	}
}

#endif
