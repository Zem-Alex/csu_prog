#include <iostream>
#include <glut.h>
#include "timer.hpp"
#include "init.hpp"
#include "draw.hpp"

using namespace std;

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WinWid, WinHei);

	glutInitWindowPosition(400, 150);

	glutCreateWindow("3d");

	glutDisplayFunc(draw);

	glutTimerFunc(60, timer, 0);
	glutTimerFunc(60, timer2, 0);

	init();

	glutMainLoop();
}