#pragma once

#include <iostream>
#include <glut.h>

using namespace std;

float WinWid = 400, WinHei = 400;

float angle = 0.0, scale = 1.0;

void init() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -200.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
}