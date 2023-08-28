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

void GUI::drawHex(float x, float y, std::vector<float> c) {
	//draw the hex
	glBegin(GL_POLYGON);
	glColor3f(c.at(0), c.at(1), c.at(2));
	glVertex2d(x - hexSize / 1.5, y);
	glVertex2d(x - hexSize / 3., y + hexSize / 2.);
	glVertex2d(x + hexSize / 3., y + hexSize / 2.);
	glVertex2d(x + hexSize / 1.5, y);
	glVertex2d(x + hexSize / 3., y - hexSize / 2.);
	glVertex2d(x - hexSize / 3., y - hexSize / 2.);
	glEnd();

	//add the hex to the list of hexes
	if (hexes.size() >= 91) return;
	Hex hex;
	hex.xcoords.push_back(((x - hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y - hexSize / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x - hexSize / 1.5) + 1) / 2 * screenWidth); hex.ycoords.push_back(( y +      1) / 2 * screenHeight);
	hex.xcoords.push_back(((x - hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y + hexSize / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y + hexSize / 2.) + 1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + hexSize / 1.5) + 1) / 2 * screenWidth); hex.ycoords.push_back(( y +      1) / 2 * screenHeight);
	hex.xcoords.push_back(((x + hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y - hexSize / 2.) + 1) / 2 * screenHeight);

	if (hexes.empty()) 
		hex.id = 0;
	else 
		hex.id = hexes.back().id + 1;

	hex.x_c = x;
	hex.y_c = y;
	hexes.push_back(hex);
}

void GUI::drawPawn(float x, float y, Colour c) {
	drawLine(x, y - pieceSize / 3., x, y + pieceSize / 3., c);
}
void GUI::drawRook(float x, float y, Colour c) {
	float xratio = 0.866; //sqrt(3)/2
	float yratio = 0.5;

	drawLine(x, y - pieceSize / 2., x, y + pieceSize / 2., c);
	drawLine(x - pieceSize / 2. * xratio, y + pieceSize / 2. * yratio, x + pieceSize / 2. * xratio, y - pieceSize / 2. * yratio, c);
	drawLine(x + pieceSize / 2. * xratio, y + pieceSize / 2. * yratio, x - pieceSize / 2. * xratio, y - pieceSize / 2. * yratio, c);
}
void GUI::drawBishop(float x, float y, Colour c) {
	float xratio = 0.5;
	float yratio = 0.866;
	drawLine(x - pieceSize / 2., y, x + pieceSize / 2., y, c);
	drawLine(x - pieceSize / 2. * xratio, y + pieceSize / 2. * yratio, x + pieceSize / 2. * xratio, y - pieceSize / 2. * yratio, c);
	drawLine(x - pieceSize / 2. * xratio, y - pieceSize / 2. * yratio, x + pieceSize / 2. * xratio, y + pieceSize / 2. * yratio, c);
}
void GUI::drawKnight(float x, float y, Colour c) {
	float ratio = 0.71;
	drawLine(x, y - pieceSize / 2. * ratio, x, y + pieceSize / 2. * ratio, c);
	drawLine(x - pieceSize / 2. * ratio, y, x + pieceSize / 2. * ratio, y, c);

	drawLine(x - pieceSize / 2. * ratio, y, x - pieceSize / 2., y + pieceSize / 4., c);
	drawLine(x - pieceSize / 2. * ratio, y, x - pieceSize / 2., y - pieceSize / 4., c);

	drawLine(x + pieceSize / 2. * ratio, y, x + pieceSize / 2., y + pieceSize / 4., c);
	drawLine(x + pieceSize / 2. * ratio, y, x + pieceSize / 2., y - pieceSize / 4., c);

	drawLine(x, y - pieceSize / 2. * ratio, x - pieceSize / 4., y - pieceSize / 2., c);
	drawLine(x, y - pieceSize / 2. * ratio, x + pieceSize / 4., y - pieceSize / 2., c);
	
	drawLine(x, y + pieceSize / 2. * ratio, x - pieceSize / 4., y + pieceSize / 2., c);
	drawLine(x, y + pieceSize / 2. * ratio, x + pieceSize / 4., y + pieceSize / 2., c);

}
void GUI::drawQueen(float x, float y, Colour c) {
	float ratio = 0.71;
	drawRook(x, y, c);
	drawBishop(x, y, c);
}
void GUI::drawKing(float x, float y, Colour c) {
	drawLine(x - pieceSize / 3.0, y + pieceSize / 2., x + pieceSize / 3.0, y + pieceSize / 2., c);
	drawLine(x + pieceSize / 3.0, y + pieceSize / 2., x + pieceSize / 1.5, y                 , c);
	drawLine(x + pieceSize / 1.5, y                 , x + pieceSize / 3.0, y - pieceSize / 2., c);
	drawLine(x + pieceSize / 3.0, y - pieceSize / 2., x - pieceSize / 3.0, y - pieceSize / 2., c);
	drawLine(x - pieceSize / 3.0, y - pieceSize / 2., x - pieceSize / 1.5, y                 , c);
	drawLine(x - pieceSize / 1.5, y                 , x - pieceSize / 3.0, y + pieceSize / 2., c);

}

//-public-------

void GUI::drawBoard() {

	//move the start point to the bottom left
	double init_x = -hexSize * 5;
	double init_y = -hexSize * 2.5;
	
	double x = init_x;
	double y = init_y;

	std::vector<int> dark = { 1,4,9,12,15,18,21,22,25,28,33,36,39,42,45,48,51,54,57,60,62,65,68,72,75,78,81,84,86,89 };
	std::vector<int> med = { 2,5,7,10,13,16,19,23,26,29,31,34,37,40,43,46,49,52,55,58,61,63,66,69,73,76,79,82,85,87,90};
	std::vector<int> light = { 3,6,8,11,14,17,20,24,27,30,32,35,38,41,44,47,50,53,56,59,64,67,70,71,74,77,80,83,88,91};


	int filesz = 6;
	int counter = 0;
	for (int rank = 0; rank < 11; rank++) {
		rank < 6 ? x = init_x : x = init_x + hexSize * (rank - 5);
		y = init_y + hexSize * rank;
		if (rank > 5) y -= (hexSize / 2.) * (rank - 5);

		for (int file = 0; file < filesz; file++) {
			counter++;
			std::vector<float> colour;
			if (std::count(dark.begin(), dark.end(), counter) != 0)
				colour = { 0.25, 0.2, 0.2 };
			else if (std::count(med.begin(), med.end(), counter) != 0)
				colour = { 0.5, 0.45, 0.45 };
			else if (std::count(light.begin(), light.end(), counter) != 0)
				colour = { 0.75, 0.7, 0.7 };

			drawHex(x, y, colour);
			x += hexSize;
			y -= hexSize / 2.;
			
		}
		rank < 5 ? filesz++ : filesz--;
	}
}

void GUI::drawPiece(Hex hex, Colour c, Type t) {

	float x = hex.x_c;
	float y = hex.y_c;
	
	if (t == pawn) drawPawn(x, y, c);
	else if (t == rook) drawRook(x, y, c);
	else if (t == bishop) drawBishop(x, y, c);
	else if (t == knight) drawKnight(x, y, c);
	else if (t == queen) drawQueen(x, y, c);
	else if (t == king) drawKing(x, y, c);
}

void GUI::drawSelectedHex(Hex hex) {
	float x = hex.x_c;
	float y = hex.y_c;

	std::vector<float> c = { 1., 0.5, 0.1 };
	drawHex(x, y, c);
}

void GUI::drawAttacks(std::bitset<92> attacks, std::bitset<92> occupied) {
	for (int i = 0; i < 91; i++) {
		if (!attacks.test(i)) continue;

		double cx = hexes[i].x_c;
		double cy = hexes[i].y_c;

		glBegin(GL_LINE_LOOP);

		occupied.test(i) ? glColor3f(0.75f, 0.0f, 0.0f): glColor3f(0.0f, 0.75f, 0.0f);
		for (int j = 0; j < 20; j++) {
			float theta = 2.0f * 3.1415926f * float(j) / float(20);//get the current angle 
			float x = pieceSize / 2 * cosf(theta);//calculate the x component 
			float y = pieceSize / 2 * sinf(theta);//calculate the y component 
			glVertex2f(x + cx, y + cy);//output vertex 
		}
		glEnd();
	}
}