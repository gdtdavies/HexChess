#pragma once

#include <bitset>
#include <vector>
#include "Enums.h"
#include "Bitboards.h"

using namespace std;

class LookupBitboard {
private:
	bitset<115> WpawnMoves[115], BpawnMoves[115];
	bitset<115> WpawnAttacks[115], BpawnAttacks[115];
	bitset<115> knightAttacks[115];
	bitset<115> kingAttacks[115];

	bitset<115> rayAttacks[115][12];
	

	inline bool isNegative(Direction dir) { return dir < 0; }
	int bitScan(bitset<115> mask, bool isNegative);
	bitset<115> getRayAttacks(bitset<115> occupied, Direction dir, Tile hex);

	inline bitset<115> cornerAttacks1(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, CornerW, hex) | getRayAttacks(occupied, CornerE, hex); }
	inline bitset<115> cornerAttacks2(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, CornerSW, hex) | getRayAttacks(occupied, CornerNE, hex); }
	inline bitset<115> cornerAttacks3(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, CornerNW, hex) | getRayAttacks(occupied, CornerSE, hex); }
			 
	inline bitset<115> edgeAttacks1(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, EdgeN, hex) | getRayAttacks(occupied, EdgeS, hex); }
	inline bitset<115> edgeAttacks2(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, EdgeSW, hex) | getRayAttacks(occupied, EdgeNE, hex); }
	inline bitset<115> edgeAttacks3(bitset<115> occupied, Tile hex) { return getRayAttacks(occupied, EdgeNW, hex) | getRayAttacks(occupied, EdgeSE, hex); }

public:
	void setPawnAttacks(BitBoard& bb);
	void setPawnMoves(BitBoard& bb);
	void setKnightAttacks(BitBoard& bb);
	void setKingAttacks(BitBoard& bb);
	void setRayAttacks(BitBoard& bb);

	
	inline bitset<115> getPawnAttacks(BitBoard& bb, Tile pos, Colour c) { return c == white ? (WpawnAttacks[pos] & bb.Bpieces) : (BpawnAttacks[pos] & bb.Wpieces); }
	inline bitset<115> getPawnMoves(BitBoard& bb, Tile pos, Colour c) { return c == white ? (WpawnMoves[pos] & ~bb.Occupied) : (BpawnMoves[pos] & ~bb.Occupied); }
	inline bitset<115> getKnightAttacks(BitBoard& bb, Tile pos, Colour c) { return c == white ? (knightAttacks[pos] & ~bb.Wpieces) : (knightAttacks[pos] & ~bb.Bpieces); }
	inline bitset<115> getKingAttacks(BitBoard& bb, Tile pos, Colour c) { return c == white ? (kingAttacks[pos] & ~bb.Wpieces) : (kingAttacks[pos] & ~bb.Bpieces); }
	inline bitset<115> getRookAttacks(BitBoard &bb, Tile pos, Colour c){
		bitset<115> active_colour = c == white ? bb.Wpieces : bb.Bpieces;
		return (edgeAttacks1(bb.Occupied, pos) | edgeAttacks2(bb.Occupied, pos) | edgeAttacks3(bb.Occupied, pos)) & ~active_colour;
	}
	inline bitset<115> getBishopAttacks(BitBoard &bb, Tile pos, Colour c){
		bitset<115> active_colour = c == white ? bb.Wpieces : bb.Bpieces;
		return (cornerAttacks1(bb.Occupied, pos) | cornerAttacks2(bb.Occupied, pos) | cornerAttacks3(bb.Occupied, pos)) & ~active_colour;
	}
	inline bitset<115> getQueenAttacks(BitBoard &bb, Tile pos, Colour c){
		return getRookAttacks(bb, pos, c) | getBishopAttacks(bb, pos, c);
	}
};
