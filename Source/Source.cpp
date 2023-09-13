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

//-header files-
#include "../Headers/Bitboards.h"
BitBoard bb;
#include "../Headers/LookupBitboards.h"
LookupBitboard LuBB; 

#include "../Headers/GUI.h"
GUI gui;

#include "../Headers/Move.h"
#include "../Headers/Enums.h"

glm::mat4 ViewMatrix, ProjectionMatrix;

//-global vars--
Tile selectedHex = none;
Colour turn = NA;

bool gameOver = false;

//-function defs-
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

	LuBB.setPawnMoves(bb);
	LuBB.setPawnAttacks(bb);
	LuBB.setKnightAttacks(bb);
	LuBB.setKingAttacks(bb);
	LuBB.setRayAttacks(bb);
}

void display() {
	//clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT);

	ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));

	glEnable(GL_BLEND);
	
	gui.drawBoard();
	
	//displaying the selected hex
	if (selectedHex != none) {
		gui.drawSelectedHex(selectedHex);

		//displaying the attacked hexes
		for (int attack = 0; attack < hex_count; attack++) {
			if (bb.SkipHexes.test(attack)) continue;
			Move m = Move(selectedHex, (Tile)attack, bb.getTypeInHex(selectedHex), turn);
			m.setTakenType(bb.getTypeInHex((Tile)attack));
		
			if (m.isLegal(bb, LuBB))
				gui.drawAttack((Tile)attack, bb.Occupied);
		}
	}
	
	//displaying the pieces
	for (int hex = 0; hex < hex_count; hex++) {
		if (!bb.Occupied.test(hex)) continue;
		gui.drawPiece((Tile)hex, bb.getColourInHex((Tile)hex), bb.getTypeInHex((Tile)hex));
	}

	glDisable(GL_BLEND);
	glutSwapBuffers();
}

void reshape(int w, int h) {
	gui.screenWidth = w;
	gui.screenHeight = h;

	// the size of a hex the one 11th of the board which is 95% of the screen
	gui.hexSize = (gui.screenWidth < gui.screenHeight ? gui.screenWidth : gui.screenHeight) / 11.0 * 1.9; 
	gui.hexSize /= (gui.screenWidth < gui.screenHeight ? gui.screenWidth : gui.screenHeight); // normalise hexSize
	gui.pieceSize = gui.hexSize * 0.67; // a piece is two thrirds the size of a hex

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
	//reverse the y value so 0 is at the bottom of the screen
	y = gui.screenHeight - y;

	if (gameOver) return;
	
	bool moveMade = false;
	for (int hex = 0; hex < hex_count; hex++) {
		if (moveMade) continue;
		if (bb.SkipHexes.test(hex)) continue;
		//check if the click was inside the hex
		if (!isInside_hex(gui.hexes[hex].xcoords, gui.hexes[hex].ycoords, x, y)) continue;

		//find the bitset that maps the pieces of the active player
		bitset<hex_count> active_colour = turn == white ? bb.Wpieces : turn == black ? bb.Bpieces : bb.Occupied;

		//return if no hex is currently selected and the hex is not occupied
		if (selectedHex == none && !bb.Occupied.test(hex)) return;

		//deselect the hex and return if it was the one already selected
		if (selectedHex == hex) {
			selectedHex = none;
			return;
		}
		//select the new hex and return if the colour matches the turn
		if (active_colour.test(hex)) {
			selectedHex = (Tile)hex;
			return;
		}
		if (selectedHex == none) continue;

		//create a move object for the current move
		Move move = Move(selectedHex, (Tile)hex, bb.getTypeInHex(selectedHex), turn);
		move.setTakenType(bb.getTypeInHex((Tile)hex));

		//make the move, swap the turn, and delselect the hex if the move is legal
		if (move.isLegal(bb, LuBB)) {
			move.run(bb);
			
			//end the game if it is checkmate
			if (move.isCheckmate(bb, LuBB)) {
				gameOver = true;
				cout << "checkmate << " << (turn == white ? "white" : "black") << " wins >>" << endl;
			}
			//end the game if it is stalemate
			else if (move.isStalemate(bb, LuBB)) {	
				gameOver = true;
				cout << "Stalemate" << endl;
			}
			//end the game if it is a draw
			else if (move.isDraw(bb)) {
				gameOver = true;
				cout << "Draw" << endl;
			}
			
			selectedHex = none;
			turn = turn == white ? black : white;
			moveMade = true;

			cout << bb.EnPassents << endl;

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

Tile strToTile(string str) {
	if (str == "a1") return a1;
	else if (str == "a2") return a2;
	else if (str == "a3") return a3;
	else if (str == "a4") return a4;
	else if (str == "a5") return a5;
	else if (str == "a6") return a6;
	
	else if (str == "b6") return b1;
	else if (str == "b2") return b2;
	else if (str == "b3") return b3;
	else if (str == "b4") return b4;
	else if (str == "b5") return b5;
	else if (str == "b6") return b6;
	else if (str == "b7") return b7;

	else if (str == "c6") return c1;
	else if (str == "c2") return c2;
	else if (str == "c3") return c3;
	else if (str == "c4") return c4;
	else if (str == "c5") return c5;
	else if (str == "c6") return c6;
	else if (str == "c7") return c7;
	else if (str == "c8") return c8;

	else if (str == "d6") return d1;
	else if (str == "d2") return d2;
	else if (str == "d3") return d3;
	else if (str == "d4") return d4;
	else if (str == "d5") return d5;
	else if (str == "d6") return d6;
	else if (str == "d7") return d7;
	else if (str == "d8") return d8;
	else if (str == "d9") return d9;

	else if (str == "e6") return e1;
	else if (str == "e2") return e2;
	else if (str == "e3") return e3;
	else if (str == "e4") return e4;
	else if (str == "e5") return e5;
	else if (str == "e6") return e6;
	else if (str == "e7") return e7;
	else if (str == "e8") return e8;
	else if (str == "e9") return e9;
	else if (str == "e10") return e10;

	else if (str == "f6") return f1;
	else if (str == "f2") return f2;
	else if (str == "f3") return f3;
	else if (str == "f4") return f4;
	else if (str == "f5") return f5;
	else if (str == "f6") return f6;
	else if (str == "f7") return f7;
	else if (str == "f8") return f8;
	else if (str == "f9") return f9;
	else if (str == "f10") return f10;
	else if (str == "f11") return f11;

	else if (str == "g2") return g2;
	else if (str == "g3") return g3;
	else if (str == "g4") return g4;
	else if (str == "g5") return g5;
	else if (str == "g6") return g6;
	else if (str == "g7") return g7;
	else if (str == "g8") return g8;
	else if (str == "g9") return g9;
	else if (str == "g10") return g10;
	else if (str == "g11") return g11;

	else if (str == " h3") return h3;
	else if (str == " h4") return h4;
	else if (str == " h5") return h5;
	else if (str == " h6") return h6;
	else if (str == " h7") return h7;
	else if (str == " h8") return h8;
	else if (str == " h9") return h9;
	else if (str == " h10") return h10;
	else if (str == " h11") return h11;

	else if (str == " i4") return i4;
	else if (str == " i5") return i5;
	else if (str == " i6") return i6;
	else if (str == " i7") return i7;
	else if (str == " i8") return i8;
	else if (str == " i9") return i9;
	else if (str == " i10") return i10;
	else if (str == " i11") return i11;

	else if (str == " j5") return j5;
	else if (str == " j6") return j6;
	else if (str == " j7") return j7;
	else if (str == " j8") return j8;
	else if (str == " j9") return j9;
	else if (str == " j10") return j10;
	else if (str == " j11") return j11;

	else if (str == " k6") return k6;
	else if (str == " k7") return k7;
	else if (str == " k8") return k8;
	else if (str == " k9") return k9;
	else if (str == " k10") return k10;
	else if (str == " k11") return k11;
	
	return none;
}

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
	bb.Wpawns.reset(); bb.Wrooks.reset(); bb.Wknights.reset();
	bb.Wbishops.reset(); bb.Wqueens.reset(); bb.Wking.reset();

	bb.Bpawns.reset(); bb.Brooks.reset(); bb.Bknights.reset();
	bb.Bbishops.reset(); bb.Bqueens.reset(); bb.Bking.reset();

	
	
	int hex = 2;
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
		
		if (c == '/') {
			while (!bb.Bottom.test(hex))hex++;
			continue;
		}
		//set the bit in the bitboard to 1
		c == 'p' ? bb.Wpawns.set(hex)
			: c == 'P' ? bb.Bpawns.set(hex)
			: c == 'r' ? bb.Wrooks.set(hex)
			: c == 'R' ? bb.Brooks.set(hex)
			: c == 'n' ? bb.Wknights.set(hex)
			: c == 'N' ? bb.Bknights.set(hex)
			: c == 'b' ? bb.Wbishops.set(hex)
			: c == 'B' ? bb.Bbishops.set(hex)
			: c == 'q' ? bb.Wqueens.set(hex)
			: c == 'Q' ? bb.Bqueens.set(hex)
			: c == 'k' ? bb.Wking.set(hex)
			: c == 'K' ? bb.Bking.set(hex)
			: __noop;
		hex++;
	}

	bb.Wpieces = bb.Wpawns | bb.Wrooks | bb.Wknights | bb.Wbishops | bb.Wqueens | bb.Wking;
	bb.Bpieces = bb.Bpawns | bb.Brooks | bb.Bknights | bb.Bbishops | bb.Bqueens | bb.Bking;

	bb.Occupied = bb.Wpieces | bb.Bpieces;
	

	//=Active Colour=========================================================1=|
	turn = fen_info[1] == "w" ? white : fen_info[1] == "b" ? black : NA;
	
	//=Possible En Passant Targets===========================================2=|
	if (fen_info[2] != "-") bb.EnPassents = 0;
	else bb.EnPassents = 1 << strToTile(fen_info[2]);
	
	//=Halfmove Clock========================================================3=|
	if (fen_info[3] != "-") bb.halfMC = stoi(fen_info[3]);
	else bb.halfMC = 0;
	
	//=Fullmove Number=======================================================4=|
	if (fen_info[4] != "-") bb.fullMC = stoi(fen_info[3]);
	else bb.fullMC = 0;
	
}

//=Main Function======================||==================||==================||==================>>

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

	loadFromFen("6/p5P/rp4PR/n1p3P1N/q2p2P2Q/bbb1p1P1BBB/k2p2P2K/n1p3P1N/rp4PR/p5P/6 w - 0 1");
	//loadFromFen("1prnqb/2p2bk/3p1b1n/4p3r/5ppppp/11/PPPPP5/R3P4/N1B1P3/QB2P2/BKNRP1 w - 0 1");

	//checkmate test with qi9 | stalemate test with qi8
	//loadFromFen("1r4/7/8/9/10/11/10/9/8/3q3/5K w - 99 1");

	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}