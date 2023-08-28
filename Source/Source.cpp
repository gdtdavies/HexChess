#include<iostream>
#include<string>
#include<tuple>

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
	
	for (int hex = 0; hex < 91; hex++) {
		if (!Occupied.test(hex)) continue;


		float x = gui.hexes[hex].x_c;
		float y = gui.hexes[hex].y_c;

		if (Wpawns.test(hex)) gui.drawPiece(x, y, white, pawn);
		else if (Bpawns.test(hex)) gui.drawPiece(x, y, black, pawn);
		else if (Wrooks.test(hex)) gui.drawPiece(x, y, white, rook);
		else if (Brooks.test(hex)) gui.drawPiece(x, y, black, rook);
		else if (Wknights.test(hex)) gui.drawPiece(x, y, white, knight);
		else if (Bknights.test(hex)) gui.drawPiece(x, y, black, knight);
		else if (Wbishops.test(hex)) gui.drawPiece(x, y, white, bishop);
		else if (Bbishops.test(hex)) gui.drawPiece(x, y, black, bishop);
		else if (Wqueens.test(hex)) gui.drawPiece(x, y, white, queen);
		else if (Bqueens.test(hex)) gui.drawPiece(x, y, black, queen);
		else if (Wking.test(hex)) gui.drawPiece(x, y, white, king);
		else if (Bking.test(hex)) gui.drawPiece(x, y, black, king);
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

int orientation(tuple<float, float> p, tuple<float, float> q, tuple<float, float> r) {
	//returns the side the point r is on relative to the pq segment
	double val = (get<1>(q) - get<1>(p)) * (get<0>(r) - get<0>(q)) - (get<0>(q) - get<0>(p)) * (get<1>(r) - get<1>(q));
	return val == 0 ? 0 : val > 0 ? 1 : 2; 
}

bool isIntersection(tuple<float, float> p1, tuple<float, float> q1, tuple<float, float> p2, tuple<float, float> q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	return (o1 != o2 && o3 != o4);
}

bool isInside_hex(vector<float> xcoords, vector<float> ycoords, int x, int y) {	
	tuple<float, float> click = make_tuple(x, y);
	
	tuple<float, float> down = make_tuple(x, y - 100);
	tuple<float, float> up = make_tuple(x, y + 100);

	tuple<float, float> left = make_tuple(x - 100, y);
	tuple<float, float> right = make_tuple(x + 100, y);

	tuple<float, float> p0 = make_tuple(xcoords[0], ycoords[0]);
	tuple<float, float> p1 = make_tuple(xcoords[1], ycoords[1]);
	tuple<float, float> p2 = make_tuple(xcoords[2], ycoords[2]);
	tuple<float, float> p3 = make_tuple(xcoords[3], ycoords[3]);
	tuple<float, float> p4 = make_tuple(xcoords[4], ycoords[4]);
	tuple<float, float> p5 = make_tuple(xcoords[5], ycoords[5]);

	if (!isIntersection(click, left, p0, p1) && !isIntersection(click, left, p1, p2)) return false;
	if (!isIntersection(click, right, p3, p4) && !isIntersection(click, right, p4, p5)) return false;

	if (!isIntersection(click, up, p1, p2) && !isIntersection(click, up, p2, p3) && !isIntersection(click, up, p3, p4)) return false;
	if (!isIntersection(click, down, p4, p5) && !isIntersection(click, down, p5, p0) && !isIntersection(click, down, p0, p1)) return false;

	return true;	
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