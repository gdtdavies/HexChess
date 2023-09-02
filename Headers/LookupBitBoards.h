#pragma once

#include <bitset>
#include "Enums.h"

using namespace std;

class LookupBitboard {
private:
	bitset<115> WpawnMoves[115], BpawnMoves[115];
	bitset<115> WpawnAttacks[115], BpawnAttacks[115];
	bitset<115> knightAttacks[115];
	bitset<115> kingAttacks[115];

	bitset<115> rayAttacks[12][115];
	const enum Direction : int {
		EdgeNW = -10, EdgeN = 1, EdgeNE = 11, EdgeSE = 10, EdgeS = -1, EdgeSW = -11,
		CornerW = -21, CornerNW = -9, CornerNE = 12, CornerE = 21, CornerSE = 9, CornerSW = -12
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
	inline bitset<115> getPawnAttacks(Tile pos, Colour c) {
		return c == Colour::white ? WpawnAttacks[pos] : BpawnAttacks[pos];
	}
	void setPawnMoves();
	inline bitset<115> getPawnMoves(Tile pos, Colour c) {
		return c == Colour:: white ? WpawnMoves[pos] : BpawnMoves[pos];
	}

	void setKnightAttacks();
	inline bitset<115> getKnightAttacks(Tile pos) {
		return knightAttacks[pos];
	}
	
	void setKingAttacks();
	inline bitset<115> getKingAttacks(Tile pos) {
		return kingAttacks[pos];
	}
	
	//void setRayAttacks();
	//bitset<92> getRookAttacks(Tile pos);
	//bitset<92> getBishopAttacks(Tile pos);
	//bitset<92> getQueenAttacks(Tile pos);
};
