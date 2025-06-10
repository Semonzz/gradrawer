#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cctype>
#include <string>

#include "glut.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

struct Point {
	double x, y;
	void draw(int r, int g, int b) {
		glPointSize(3);
		glColor3f(r, g, b);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		glFlush();
	}
};