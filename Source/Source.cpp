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

void loadFromFen(string fen);

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
	
	for (int sq = 0; sq < 91; sq++) {
		if (!Occupied.test(sq)) continue;


		float x = gui.hexes[sq].x_c;
		float y = gui.hexes[sq].y_c;

		if (Wpawns.test(sq)) gui.drawPiece(x, y, white, pawn);
		else if (Bpawns.test(sq)) gui.drawPiece(x, y, black, pawn);
		else if (Wrooks.test(sq)) gui.drawPiece(x, y, white, rook);
		else if (Brooks.test(sq)) gui.drawPiece(x, y, black, rook);
		else if (Wknights.test(sq)) gui.drawPiece(x, y, white, knight);
		else if (Bknights.test(sq)) gui.drawPiece(x, y, black, knight);
		else if (Wbishops.test(sq)) gui.drawPiece(x, y, white, bishop);
		else if (Bbishops.test(sq)) gui.drawPiece(x, y, black, bishop);
		else if (Wqueens.test(sq)) gui.drawPiece(x, y, white, queen);
		else if (Bqueens.test(sq)) gui.drawPiece(x, y, black, queen);
		else if (Wking.test(sq)) gui.drawPiece(x, y, white, king);
		else if (Bking.test(sq)) gui.drawPiece(x, y, black, king);
	}

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

		if (Rank01.test(hex.id)) cout << "rank 1" << endl;
		if (Rank06.test(hex.id)) cout << "rank 6" << endl;
		if (Rank11.test(hex.id)) cout << "rank 11" << endl;

		if (selectedHex == none) {
			selectedHex = static_cast<Hexagon>(hex.id);
			//cout << "selected hexagon " << hex.id << endl;
			return;
		}
		else if (selectedHex == hex.id) {
			selectedHex = none;
			//cout << "deselected hexagon " << hex.id << endl;
			return;
		}
		else {
			//check the piece can move to the hex
			//if it can
			//		move the piece and deselect the hex
			//else 
			//		do nothing
			selectedHex = static_cast<Hexagon>(hex.id);
			//cout << "selected hexagon " << hex.id << endl;
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

void loadFromFen(string fen) {
	
	string fen_info[5] = { "", "", "", "", "" };
	
	//=split the fen into componants===========================================|
	string info = "";
	int counter = 0;
	for (char c : fen) {
		if (c == ' ') {
			fen_info[counter] = info;
			info = "";
			counter++;
		}
		else
			info += c;
	}

	//=Piece Positions=======================================================0=|
	Wpawns.reset(); Wrooks.reset(); Wknights.reset();
	Wbishops.reset(); Wqueens.reset(); Wking.reset();

	Bpawns.reset(); Brooks.reset(); Bknights.reset();
	Bbishops.reset(); Bqueens.reset(); Bking.reset();
	
	int hex = 0;
	for (int i = 0; i < fen_info[0].length(); i++) {
		//fen format is: "piece_pos active_colour ep_hexes half_move_counter full_move_counter"
		char c = fen_info[0][i];
		if (isdigit(c)) {
			// check if the number is two digits
			if (c == '1' && i + 1 < fen_info[0].length() && isdigit(fen_info[0][i + 1])) {
				hex += 10 + int(fen_info[0][i + 1]) - 48;
				i++;
			}
			else 
				hex += int(c) - 48;
			continue; 
		}
		
		if (c == '/') continue;
		//set the bit in the bitboard to 1
		c == 'p' ? Wpawns.set(hex)
			: c == 'P' ? Bpawns.set(hex)
			: c == 'r' ? Wrooks.set(hex)
			: c == 'R' ? Brooks.set(hex)
			: c == 'n' ? Wknights.set(hex)
			: c == 'N' ? Bknights.set(hex)
			: c == 'b' ? Wbishops.set(hex)
			: c == 'B' ? Bbishops.set(hex)
			: c == 'q' ? Wqueens.set(hex)
			: c == 'Q' ? Bqueens.set(hex)
			: c == 'k' ? Wking.set(hex)
			: c == 'K' ? Bking.set(hex)
			: __noop;
		hex++;
	}

	Wpieces = Wpawns | Wrooks | Wknights | Wbishops | Wqueens | Wking;
	Bpieces = Bpawns | Brooks | Bknights | Bbishops | Bqueens | Bking;

	Occupied = Wpieces | Bpieces;
	

	//=Active Colour=========================================================1=|
	//TODO
	
	//=Possible En Passant Targets===========================================2=|
	//TODO
	
	//=Halfmove Clock========================================================3=|
	//TODO
	
	//=Fullmove Number=======================================================4=|
	//TODO
	
}

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

	loadFromFen("1prnqb/2p2bk/3p1b1n/4p3r/5ppppp/11/PPPPP5/R3P4/N1B1P3/QB2P2/BKNRP1 w - 0 1");
	//loadFromFen("6/pPpPpPp/8/PpPpPpPpP/10/pPpPpPpPpPp/10/PpPpPpPpP/8/pPpPpPp/6 w - 0 1");

	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}