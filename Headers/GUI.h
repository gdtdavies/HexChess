#pragma once
#include "../Headers/Enums.h"
#include <vector>

class GUI {
private:
	void drawLine(float x1, float y1, float x2, float y2, Colour c);
	void drawHex(float x, float y, double sz, std::vector<float> c);
	
public:
	double screenWidth = 1000, screenHeight = 1000;
	double hexSize;
	
	void drawBoard();
};
