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

#include "../Headers/GUI.h"
GUI gui;


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
	gui.drawPiece(0, 6, white, queen);

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
	gui.drawPiece(9, 6, black, queen);

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
	//glutMouseFunc(mouseCallback);
	glutPostRedisplay();
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

	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}