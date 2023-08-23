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

int screenWidth = 1000, screenHeight = 1000;
double sqW, sqH;
glm::mat4 ViewMatrix, ProjectionMatrix;


void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); //sets the clear colour to black
	glLineWidth(3.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display() {

}

void reshape(int w, int h) {
	screenWidth = w;
	screenHeight = h;


	sqW = w / 8 * 1.75;
	sqH = h / 8 * 1.75;

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
	glutInitWindowSize(screenWidth, screenHeight);
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