#include "../Headers/GUI.h"
#include "../Headers/Hex.h"

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


//-private------
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
	//draw the hex
	glBegin(GL_POLYGON);
	glColor3f(c.at(0), c.at(1), c.at(2));
	glVertex2d(x - sz / 1.5, y);
	glVertex2d(x - sz / 3., y + sz / 2.);
	glVertex2d(x + sz / 3., y + sz / 2.);
	glVertex2d(x + sz / 1.5, y);
	glVertex2d(x + sz / 3., y - sz / 2.);
	glVertex2d(x - sz / 3., y - sz / 2.);
	glEnd();

	//add the hex to the list of hexes
	if (hexes.size() >= 91) return;
	Hex hex;
	hex.xcoords.push_back(((x - sz / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y - sz / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x - sz / 1.5) + 1) / 2 * screenWidth);	hex.ycoords.push_back(( y            + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x - sz / 3.0) + 1) / 2 * screenWidth);	hex.ycoords.push_back(((y + sz / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + sz / 3.0) + 1) / 2 * screenWidth);	hex.ycoords.push_back(((y + sz / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + sz / 1.5) + 1) / 2 * screenWidth);	hex.ycoords.push_back(( y            + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + sz / 3.0) + 1) / 2 * screenWidth);	hex.ycoords.push_back(((y - sz / 2.) + 1) / 2 * screenHeight);

	if (hexes.empty()) 
		hex.id = 0;
	else 
		hex.id = hexes.back().id + 1;

	hex.x_c = x;
	hex.y_c = y;
	hexes.push_back(hex);
}

void GUI::drawPawn(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	drawLine(x, y - sz / 3., x, y + sz / 3., c);
}
void GUI::drawRook(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	float xratio = 0.866; //sqrt(3)/2
	float yratio = 0.5;

	//drawLine(x - sz / 2., y, x + sz / 2., y, c);
	drawLine(x, y - sz / 2., x, y + sz / 2., c);
	drawLine(x - sz / 2. * xratio, y + sz / 2. * yratio, x + sz / 2. * xratio, y - sz / 2. * yratio, c);
	drawLine(x + sz / 2. * xratio, y + sz / 2. * yratio, x - sz / 2. * xratio, y - sz / 2. * yratio, c);
}
void GUI::drawBishop(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	float xratio = 0.5;
	float yratio = 0.866;
	drawLine(x - sz / 2., y, x + sz / 2., y, c);
	drawLine(x - sz / 2. * xratio, y + sz / 2. * yratio, x + sz / 2. * xratio, y - sz / 2. * yratio, c);
	drawLine(x - sz / 2. * xratio, y - sz / 2. * yratio, x + sz / 2. * xratio, y + sz / 2. * yratio, c);
}
void GUI::drawKnight(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	float ratio = 0.71;
	drawLine(x, y - sz / 2. * ratio, x, y + sz / 2. * ratio, c);
	drawLine(x - sz / 2. * ratio, y, x + sz / 2. * ratio, y, c);

	drawLine(x - sz / 2. * ratio, y, x - sz / 2., y + sz / 4., c);
	drawLine(x - sz / 2. * ratio, y, x - sz / 2., y - sz / 4., c);

	drawLine(x + sz / 2. * ratio, y, x + sz / 2., y + sz / 4., c);
	drawLine(x + sz / 2. * ratio, y, x + sz / 2., y - sz / 4., c);

	drawLine(x, y - sz / 2. * ratio, x - sz / 4., y - sz / 2., c);
	drawLine(x, y - sz / 2. * ratio, x + sz / 4., y - sz / 2., c);
	
	drawLine(x, y + sz / 2. * ratio, x - sz / 4., y + sz / 2., c);
	drawLine(x, y + sz / 2. * ratio, x + sz / 4., y + sz / 2., c);

}
void GUI::drawQueen(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	float ratio = 0.71;
	drawRook(x, y, c);
	drawBishop(x, y, c);
}
void GUI::drawKing(float x, float y, Colour c) {
	double sz = (hexSize * 0.5) / (screenWidth < screenHeight ? screenWidth : screenHeight);
	drawLine(x - sz / 2, y - sz / 2, x + sz / 2, y - sz / 2, c);
	drawLine(x + sz / 2, y - sz / 2, x + sz / 2, y + sz / 2, c);
	drawLine(x + sz / 2, y + sz / 2, x - sz / 2, y + sz / 2, c);
	drawLine(x - sz / 2, y + sz / 2, x - sz / 2, y - sz / 2, c);
}

//-public-------

void GUI::drawBoard() {
	double sz = hexSize / (screenWidth < screenHeight ? screenWidth : screenHeight);

	//move the start point to the bottom left
	double init_x = -sz * 5;
	double init_y = -sz * 2.5;
	
	double x = init_x;
	double y = init_y;

	std::vector<int> dark = { 1,4,9,12,15,18,21,22,25,28,33,36,39,42,45,48,51,54,57,60,62,65,68,72,75,78,81,84,86,89 };
	std::vector<int> med = { 2,5,7,10,13,16,19,23,26,29,31,34,37,40,43,46,49,52,55,58,61,63,66,69,73,76,79,82,85,87,90};
	std::vector<int> light = { 3,6,8,11,14,17,20,24,27,30,32,35,38,41,44,47,50,53,56,59,64,67,70,71,74,77,80,83,88,91};


	int filesz = 6;
	int counter = 0;
	for (int rank = 0; rank < 11; rank++) {
		rank < 6 ? x = init_x : x = init_x + sz * (rank - 5);
		y = init_y + sz * rank;
		if (rank > 5) y -= (sz / 2.) * (rank - 5);

		for (int file = 0; file < filesz; file++) {
			counter++;
			std::vector<float> colour;
			if (std::count(dark.begin(), dark.end(), counter) != 0)
				colour = { 0.25, 0.2, 0.2 };
			else if (std::count(med.begin(), med.end(), counter) != 0)
				colour = { 0.5, 0.45, 0.45 };
			else if (std::count(light.begin(), light.end(), counter) != 0)
				colour = { 0.75, 0.7, 0.7 };

			drawHex(x, y, sz, colour);
			x += sz;
			y -= sz / 2.;
			
		}
		rank < 5 ? filesz++ : filesz--;
	}
}

void GUI::drawPiece(float x, float y, Colour c, Type t) {
	if (t == pawn) drawPawn(x, y, c);
	else if (t == rook) drawRook(x, y, c);
	else if (t == bishop) drawBishop(x, y, c);
	else if (t == knight) drawKnight(x, y, c);
	else if (t == queen) drawQueen(x, y, c);
	else if (t == king) drawKing(x, y, c);
}