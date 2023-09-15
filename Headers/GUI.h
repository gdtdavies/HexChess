#pragma once
#include "Enums.h"
#include "Hex.h"
#include "Bitboards.h"
#include "Move.h"

#include <vector>
#include <bitset>

class GUI {
private:
	BitBoard bb;
	void drawLine(float x1, float y1, float x2, float y2, Colour c);
	void drawHex(float x, float y, std::vector<float> c);
	
	void drawPawn(float x, float y, Colour c);
	void drawRook(float x, float y, Colour c);
	void drawBishop(float x, float y, Colour c);
	void drawKnight(float x, float y, Colour c);
	void drawQueen(float x, float y, Colour c);
	void drawKing(float x, float y, Colour c);

public:
	double screenWidth = 1000, screenHeight = 1000;
	float hexSize, pieceSize;
	std::vector<Hex> hexes;
	
	void drawBoard();
	void drawPiece(Tile tile, Colour c, Type t);

	void drawSelectedHex(Tile tile);
	void drawAttack(Tile attack, bitset<hex_count> occupied);
	void drawPromotion(Colour c);
};
