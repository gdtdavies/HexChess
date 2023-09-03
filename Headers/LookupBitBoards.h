#pragma once

#include <bitset>
#include "Enums.h"
#include "Bitboards.h"

using namespace std;

class LookupBitboard {
private:
	BitBoard bb;
	bitset<115> WpawnMoves[115], BpawnMoves[115];
	bitset<115> WpawnAttacks[115], BpawnAttacks[115];
	bitset<115> knightAttacks[115];
	bitset<115> kingAttacks[115];

	bitset<115> rayAttacks[115][12];
	const enum Direction : int {
		EdgeNW = -10, EdgeN = 1, EdgeNE = 11, EdgeSE = 10, EdgeS = -1, EdgeSW = -11,
		CornerW = -21, CornerNW = -9, CornerNE = 12, CornerE = 21, CornerSE = 9, CornerSW = -12
	};

	//bool isNegative(int dir);
	//int bitScan(bitset<115> mask, bool isNegative);
	//bitset<115> getRayAttacks(bitset<115> occupied, Direction dir, Tile hex);
	//
	//bitset<115> cornerAttacks1(bitset<115> occupied, Tile hex);
	//bitset<115> cornerAttacks2(bitset<115> occupied, Tile hex);
	//bitset<115> cornerAttacks3(bitset<115> occupied, Tile hex);
	//
	//bitset<115> edgeAttacks1(bitset<115> occupied, Tile hex);
	//bitset<115> edgeAttacks2(bitset<115> occupied, Tile hex);
	//bitset<155> edgeAttacks3(bitset<115> occupied, Tile hex);

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
	
	void setRayAttacks();
	inline bitset<115> getRayAttacks(Tile pos) {
		bitset<115> attacks(0);
		for (int i = 0; i < 12; i++) {
			attacks |= rayAttacks[pos][i];
		}
		return attacks;
	}
	//inline bitset<115> getRookAttacks(Tile pos);
	//inline bitset<115> getBishopAttacks(Tile pos);
	//inline bitset<115> getQueenAttacks(Tile pos);
};
