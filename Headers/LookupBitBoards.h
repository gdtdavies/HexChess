#pragma once

#include <bitset>
#include "Enums.h"

using namespace std;

class LookupBitboard {
private:
	bitset<92> WpawnMoves[91], BpawnMoves[91];
	bitset<92> WpawnAttacks[91], BpawnAttacks[91];
	bitset<92> knightAttacks[91];
	bitset<92> kingAttacks[91];

	bitset<92> rayAttacks[12][91];
	const enum Direction : int {
		EdgeNW, EdgeN, EdgeNE, EdgeSE, EdgeS, EdgeSW,
		CornerW, CornerNW, CornerNE, CornerE, CornerSE, CornerSW
	};

	//bool isNegative(int dir);
	//int bitScan(bitset<92> mask, bool isNegative);
	//bitset<92> getRayAttacks(bitset<92> occupied, Direction dir, Tile hex);
	//
	//bitset<92> cornerAttacks1(bitset<92> occupied, Tile hex);
	//bitset<92> cornerAttacks2(bitset<92> occupied, Tile hex);
	//bitset<92> cornerAttacks3(bitset<92> occupied, Tile hex);
	//
	//bitset<92> edgeAttacks1(bitset<92> occupied, Tile hex);
	//bitset<92> edgeAttacks2(bitset<92> occupied, Tile hex);
	//bitset<92> edgeAttacks3(bitset<92> occupied, Tile hex);

public:
	void setPawnAttacks();
	void setPawnMoves();
	bitset<92> getPawnMoves(Tile pos, Colour c);
	bitset<92> getPawnAttacks(Tile pos, Colour c);

	void setKnightAttacks();
	bitset<92> getKnightAttacks(Tile pos);
	
	//void setKingAttacks();
	//bitset<92> getKingAttacks(Tile pos);
	//
	//void setRayAttacks();
	//bitset<92> getRookAttacks(Tile pos);
	//bitset<92> getBishopAttacks(Tile pos);
	//bitset<92> getQueenAttacks(Tile pos);
};
