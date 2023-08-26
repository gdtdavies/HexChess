#include<iostream>
#include<string>

using namespace std;

//--- OpenGL ---
#include "GL/glew.h"
#include "GL/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "GL\freeglut.h"
//--------------

#include "../Headers/Enums.h"


glm::mat4 ViewMatrix, ProjectionMatrix;

#include "../Headers/Bitboards.h"
#include "../Headers/GUI.h"
GUI gui;

Hexagon selectedHex = none;



void mouseCallback(int button, int state, int x, int y);

bool isInside_hex(vector<float> xcoords, vector<float> ycoords, int x, int y);

// /================================<<--------------------------->>================================/
// /================================<< START OF OPENGL FUNCTIONS >>================================/
// /================================<<--------------------------->>================================/


void init() {
	glClearColor(0.0, 0.51, 0.51, 0.0); //sets the clear colour to black
	glLineWidth(3.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display() {
	//clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT);

	ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));

	glEnable(GL_BLEND);
	
	gui.drawBoard();

	gui.drawPiece(0, 1, white, pawn);
	gui.drawPiece(1, 2, white, pawn);
	gui.drawPiece(2, 3, white, pawn);
	gui.drawPiece(3, 4, white, pawn);
	gui.drawPiece(4, 5, white, pawn);
	gui.drawPiece(3, 6, white, pawn);
	gui.drawPiece(2, 7, white, pawn);
	gui.drawPiece(1, 8, white, pawn);
	gui.drawPiece(0, 9, white, pawn);

	gui.drawPiece(0, 2, white, rook);
	gui.drawPiece(0, 8, white, rook);

	gui.drawPiece(0, 3, white, knight);
	gui.drawPiece(0, 7, white, knight);

	gui.drawPiece(0, 4, white, queen);
	gui.drawPiece(0, 6, white, king);

	gui.drawPiece(0, 5, white, bishop);
	gui.drawPiece(1, 5, white, bishop);
	gui.drawPiece(2, 5, white, bishop);

	gui.drawPiece(6, 1, black, pawn);
	gui.drawPiece(6, 2, black, pawn);
	gui.drawPiece(6, 3, black, pawn);
	gui.drawPiece(6, 4, black, pawn);
	gui.drawPiece(6, 5, black, pawn);
	gui.drawPiece(6, 6, black, pawn);
	gui.drawPiece(6, 7, black, pawn);
	gui.drawPiece(6, 8, black, pawn);
	gui.drawPiece(6, 9, black, pawn);

	gui.drawPiece(7, 2, black, rook);
	gui.drawPiece(7, 8, black, rook);

	gui.drawPiece(8, 3, black, knight);
	gui.drawPiece(8, 7, black, knight);

	gui.drawPiece(9, 4, black, queen);
	gui.drawPiece(9, 6, black, king);

	gui.drawPiece(10, 5, black, bishop);
	gui.drawPiece(9, 5, black, bishop);
	gui.drawPiece(8, 5, black, bishop);


	glDisable(GL_BLEND);
	glutSwapBuffers();
}

void reshape(int w, int h) {
	gui.screenWidth = w;
	gui.screenHeight = h;

	gui.hexSize = (gui.screenWidth < gui.screenHeight ? gui.screenWidth : gui.screenHeight) / 11.0 * 1.9;

	glViewport(0, 0, w, h);	// set Viewport dimensions

	ProjectionMatrix = glm::ortho(-w / 2.0 - 50, w / 2.0 + 50, -h / 2.0 - 50, h / 2.0 + 50);
}

void idle() {
	glutMouseFunc(mouseCallback);
	glutPostRedisplay();
}

//=User Inputs====||==================||==================||==================||==================>>

void mouseCallback(int button, int state, int x, int y) {
	
	if (!(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)) return;

	y = gui.screenHeight - y;

	//cout << x << ", " << y << endl;
	for (int i = 0; i < gui.hexes.size(); i++){

		Hex hex = gui.hexes[i];

		if (!isInside_hex(hex.xcoords, hex.ycoords, x, y)) continue;
		//cout << "Hexagon " << hex.id << " clicked" << endl;

		//if (Rank01.test(hex.id)) cout << "rank 1" << endl;
		//if (Rank06.test(hex.id)) cout << "rank 6" << endl;
		//if (Rank11.test(hex.id)) cout << "rank 11" << endl;

		if (selectedHex == none) {
			selectedHex = static_cast<Hexagon>(hex.id);
			cout << "selected hexagon " << hex.id << endl;
			return;
		}
		else if (selectedHex == hex.id) {
			selectedHex = none;
			cout << "deselected hexagon " << hex.id << endl;
			return;
		}
		else {
			//check the piece can move to the hex
			//if it can
			//		move the piece and deselect the hex
			//else 
			//		do nothing
			selectedHex = static_cast<Hexagon>(hex.id);
			cout << "selected hexagon " << hex.id << endl;
			return;
		}

	}
}

// /==================================<<---------------------->>===================================/
// /==================================<< END OPENGL FUNCTIONS >>===================================/
// /==================================<<---------------------->>===================================/


//=Misc===========||==================||==================||==================||==================>>

bool isInside_tri(float x1, float y1, float x2, float y2, float x3, float y3, int x, int y)
{
	float a  = abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
	float a1 = abs((x *(y2 - y3) + x2*(y3 - y ) + x3*(y  - y2)) / 2.0);
	float a2 = abs((x1*(y  - y3) + x *(y3 - y1) + x3*(y1 - y )) / 2.0);
	float a3 = abs((x1*(y2 - y ) + x2*(y  - y1) + x *(y1 - y2)) / 2.0);

	return (a == a1 + a2 + a3);
}
bool isInside_hex(vector<float> xcoords, vector<float> ycoords, int x, int y) {
	return (xcoords[0] < x && x < xcoords[3] && ycoords[0] < y && y < ycoords[3])
		|| (isInside_tri(xcoords[0], ycoords[0], xcoords[1], ycoords[1], xcoords[2], ycoords[2], x, y))
		|| (isInside_tri(xcoords[3], ycoords[3], xcoords[4], ycoords[4], xcoords[5], ycoords[5], x, y));
}

//=Moving=========||==================||==================||==================||==================>>

//void movePiece(Move m)

//void undoMove()

//=End of Game====||==================||==================||==================||==================>>

//bool isCheckmate()

//bool isStalemate()

//bool isDraw()

//=Load Board=========================||==================||==================||==================>>

//TODO: make function loadFromFen(string fen)

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(gui.screenWidth, gui.screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("HexChess");

	glutReshapeFunc(reshape);

	//This initialises glew - it must be called after the window is created.
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << " GLEW ERROR" << std::endl;

	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}