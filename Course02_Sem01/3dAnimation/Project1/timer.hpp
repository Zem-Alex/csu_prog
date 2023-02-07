#pragma once

#include <iostream>
#include <glut.h>
#include "init.hpp"

using namespace std;

void timer2(int value) 
{
	glColor3f(0.1 * (rand() % 10), 0.1 * (rand() % 10), 0.1 * (rand() % 10));

	glutTimerFunc(250, timer2, 0);
}

void timer(int value) 
{
	angle++;

	glRotatef(15.0, 10.0, 20.0, 1.0);

	glutPostRedisplay();

	glutTimerFunc(80, timer, 0);
}