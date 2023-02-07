#pragma once

#include <iostream>
#include <glut.h>
#include "init.hpp"

using namespace std;

void draw()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	scale = 0.5 - abs(sin(3.14 * angle / 90.0) / sqrt(3.0) / 2);

	glRotatef(angle, 0.0, 0.0, 1.0);

	glScalef(scale, scale, 1.0);

	glBegin(GL_LINES);

	for (float i = -WinWid / 2; i <= WinWid / 2; i += 20.0)
	{
		glVertex2f(i, -WinHei / 2);
		glVertex2f(i, WinHei / 2);
	}

	for (float i = -WinWid / 2; i <= WinWid / 2; i += 20.0)
	{
		glVertex2f(-WinWid / 2, i);
		glVertex2f(WinWid / 2, i);
	}

	glEnd();

	glPopMatrix();

	glutSwapBuffers();

}