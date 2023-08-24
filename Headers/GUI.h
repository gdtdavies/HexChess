#pragma once
#include "../Headers/Enums.h"
#include "../Headers/Hex.h"
#include <vector>

class GUI {
private:
	void drawLine(float x1, float y1, float x2, float y2, Colour c);
	void drawHex(float x, float y, double sz, std::vector<float> c);
	
	void drawPawn(float x, float y, Colour c);
	void drawRook(float x, float y, Colour c);
	void drawBishop(float x, float y, Colour c);
	void drawKnight(float x, float y, Colour c);
	void drawQueen(float x, float y, Colour c);
	void drawKing(float x, float y, Colour c);
		
	
public:
	double screenWidth = 1000, screenHeight = 1000;
	double hexSize;
	std::vector<Hex> hexes;
	void drawPiece(float rank, float file, Colour c, Type t);
	
	void drawBoard();
};
