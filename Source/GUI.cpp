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
	glBegin(GL_POLYGON);
	glColor3f(c.at(0), c.at(1), c.at(2));
	glVertex2d(x - hexSize / 1.5, y);
	glVertex2d(x - hexSize / 3., y + hexSize / 2.);
	glVertex2d(x + hexSize / 3., y + hexSize / 2.);
	glVertex2d(x + hexSize / 1.5, y);
	glVertex2d(x + hexSize / 3., y - hexSize / 2.);
	glVertex2d(x - hexSize / 3., y - hexSize / 2.);
	glEnd();
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
	double init_x = -hexSize * 5;
	double init_y = -hexSize * 4.5;

	double x = init_x;
	double y = init_y;

	int counter = 0;
	for (int file = 0; file < 11; file++) {
		for (int rank = 0; rank < 11; rank++) {
			if (file % 2 == 0 && rank == 10) continue;
			std::vector<float> colour;
			
			if      (bb.DarkHexes.test(counter)) colour  = { 0.25, 0.2,  0.2  };
			else if (bb.MedHexes.test(counter)) colour   = { 0.5,  0.45, 0.45 };
			else if (bb.LightHexes.test(counter)) colour = { 0.75, 0.7,  0.7  };
			
			if (!bb.SkipHexes.test(counter)) 
				drawHex(x, y, colour);

			counter++;
		
			//add the hex to the list of hexes
			if (hexes.size() >= 115) {
				y += hexSize;
				continue;
			}
			Hex hex;
			hex.xcoords.push_back(((x - hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y - hexSize / 2.) + 1) / 2 * screenHeight);
			hex.xcoords.push_back(((x - hexSize / 1.5) + 1) / 2 * screenWidth); hex.ycoords.push_back((y  + 1)                 / 2 * screenHeight);
			hex.xcoords.push_back(((x - hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y + hexSize / 2.) + 1) / 2 * screenHeight);
			hex.xcoords.push_back(((x + hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y + hexSize / 2.) + 1) / 2 * screenHeight);
			hex.xcoords.push_back(((x + hexSize / 1.5) + 1) / 2 * screenWidth); hex.ycoords.push_back((y  + 1)                 / 2 * screenHeight);
			hex.xcoords.push_back(((x + hexSize / 3.0) + 1) / 2 * screenWidth); hex.ycoords.push_back(((y - hexSize / 2.) + 1) / 2 * screenHeight);

			if (hexes.empty())
				hex.id = 0;
			else
				hex.id = hexes.back().id + 1;

			hex.x_c = x;
			hex.y_c = y;
			hexes.push_back(hex);

			y += hexSize;
			
		}
		if (file % 2 == 1) y = init_y;
		else y = init_y - hexSize / 2.;
		x += hexSize;
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

void GUI::drawAttacks(std::bitset<115> attacks, std::bitset<115> occupied) {
	for (int i = 0; i < 115; i++) {
		if (!attacks.test(i)) continue;

		double cx = hexes[i].x_c;
		double cy = hexes[i].y_c;
		
		if (bb.DarkHexes.test(i))
			occupied.test(i) ? drawHex(cx, cy, { 0.25, 0.05, 0.05 }) : drawHex(cx, cy, { 0.05, 0.2,  0.05 });
		else if (bb.MedHexes.test(i))
			occupied.test(i) ? drawHex(cx, cy, { 0.5,  0.1,  0.1  }) : drawHex(cx, cy, { 0.1,  0.45, 0.1  });
		else if (bb.LightHexes.test(i))
			occupied.test(i) ? drawHex(cx, cy, { 0.75, 0.15, 0.15 }) : drawHex(cx, cy, { 0.15, 0.7,  0.15 });
	}
}