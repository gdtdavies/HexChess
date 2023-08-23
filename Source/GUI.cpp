#include "../Headers/GUI.h"

#include <iostream>
#include <vector>
#include <tuple>

//--- OpenGL ---
#include "GL/glew.h"
#include "GL/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "GL\freeglut.h"
//--------------

void GUI::drawLine(float x1, float y1, float x2, float y2, Colour c) {
	glBegin(GL_LINES);
	
	c == white ? glColor3f(1.0, 1.0, 1.0) 
		: c == black ? glColor3f(0.0, 0.0, 0.0) 
		: glColor3f(0.75, 0.0, 0.0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void GUI::drawHex(float x, float y, double sz, std::vector<float> c) {
	glBegin(GL_POLYGON);
	glColor3f(c.at(0), c.at(1), c.at(2));
	glVertex2d(x - sz/1.5, y);
	glVertex2d(x - sz/3., y + sz/2.);
	glVertex2d(x + sz/3., y + sz/2.);
	glVertex2d(x + sz/1.5, y);
	glVertex2d(x + sz/3., y - sz/2.);
	glVertex2d(x - sz/3., y - sz/2.);
	glEnd();
}

void GUI::drawBoard() {
	double sz = hexSize / (screenWidth < screenHeight ? screenWidth : screenHeight);
	double x = - sz * 6, y = -sz / 2 - sz * 3;
	int ranksz = 5;
	std::vector<int> dark = { 1,4,9,12,15,18,21,22,25,28,33,36,39,42,45,48,51,54,57,60,62,65,68,72,75,78,81,84,86,89 };
	std::vector<int> med = { 2,5,7,10,13,16,19,23,26,29,31,34,37,40,43,46,49,52,55,58,61,63,66,69,73,76,79,82,85,87,90};
	std::vector<int> light = { 3,6,8,11,14,17,20,24,27,30,32,35,38,41,44,47,50,53,56,59,64,67,70,71,74,77,80,83,88,91};

	int counter = 0;

	for (int file = 0; file < 11; file++) {
		x += sz;
		if (file < 6) {
			y -= (sz / 2) * file;
			ranksz++;
		}
		else {
			y += (sz / 2) * (file - 10);
			ranksz--;
		}
		for (int rank = 0; rank < ranksz; rank++) {
			counter++;
			y += sz ;

			std::vector<float> colour;

			if (std::count(dark.begin(), dark.end(), counter) != 0) 
				colour = { 0.25, 0.25, 0.25 };
			else if (std::count(med.begin(), med.end(), counter) != 0) 
				colour = { 0.5, 0.5, 0.5 };
			else if (std::count(light.begin(), light.end(), counter) != 0) 
				colour = { 0.75, 0.75, 0.75 };
			drawHex(x, y, sz, colour);

			
		}
		y = -sz / 2 - sz * 3;

	}
}