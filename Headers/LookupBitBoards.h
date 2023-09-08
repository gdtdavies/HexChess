#pragma once

#include <bitset>
#include <vector>
#include "Enums.h"
#include "Bitboards.h"

using namespace std;

class LookupBitboard {
private:
	bitset<hex_count> WpawnMoves[hex_count], BpawnMoves[hex_count];
	bitset<hex_count> WpawnAttacks[hex_count], BpawnAttacks[hex_count];
	bitset<hex_count> knightAttacks[hex_count];
	bitset<hex_count> kingAttacks[hex_count];

	bitset<hex_count> rayAttacks[hex_count][12];
	

	inline bool isNegative(Direction dir) { return dir < 0; }
	int bitScan(bitset<hex_count> mask, bool isNegative);
	bitset<hex_count> getRayAttacks(bitset<hex_count> occupied, Direction dir, Tile hex);

	inline bitset<hex_count> cornerAttacks1(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, CornerW,  hex) | getRayAttacks(occupied, CornerE,  hex); }
	inline bitset<hex_count> cornerAttacks2(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, CornerSW, hex) | getRayAttacks(occupied, CornerNE, hex); }
	inline bitset<hex_count> cornerAttacks3(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, CornerNW, hex) | getRayAttacks(occupied, CornerSE, hex); }
			 
	inline bitset<hex_count> edgeAttacks1(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, EdgeN,  hex) | getRayAttacks(occupied, EdgeS,  hex); }
	inline bitset<hex_count> edgeAttacks2(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, EdgeSW, hex) | getRayAttacks(occupied, EdgeNE, hex); }
	inline bitset<hex_count> edgeAttacks3(bitset<hex_count> occupied, Tile hex) { return getRayAttacks(occupied, EdgeNW, hex) | getRayAttacks(occupied, EdgeSE, hex); }

public:
	void setPawnAttacks(BitBoard& bb);
	void setPawnMoves(BitBoard& bb);
	void setKnightAttacks(BitBoard& bb);
	void setKingAttacks(BitBoard& bb);
	void setRayAttacks(BitBoard& bb);

	
	inline bitset<hex_count> getPawnAttacks(BitBoard& bb, Tile pos, Colour c)   { return c == white ? (WpawnAttacks[pos]  &  bb.Bpieces)  : (BpawnAttacks[pos]  &  bb.Wpieces);  }
	inline bitset<hex_count> getPawnMoves(BitBoard& bb, Tile pos, Colour c)     { return c == white ? (WpawnMoves[pos]    & ~bb.Occupied) : (BpawnMoves[pos]    & ~bb.Occupied); }
	inline bitset<hex_count> getKnightAttacks(BitBoard& bb, Tile pos, Colour c) { return c == white ? (knightAttacks[pos] & ~bb.Wpieces)  : (knightAttacks[pos] & ~bb.Bpieces);  }
	inline bitset<hex_count> getKingAttacks(BitBoard& bb, Tile pos, Colour c)   { return c == white ? (kingAttacks[pos]   & ~bb.Wpieces)  : (kingAttacks[pos]   & ~bb.Bpieces);  }
	inline bitset<hex_count> getRookAttacks(BitBoard &bb, Tile pos, Colour c){
		bitset<hex_count> active_colour = c == white ? bb.Wpieces : bb.Bpieces;
		return (edgeAttacks1(bb.Occupied, pos) | edgeAttacks2(bb.Occupied, pos) | edgeAttacks3(bb.Occupied, pos)) & ~active_colour;
	}
	inline bitset<hex_count> getBishopAttacks(BitBoard &bb, Tile pos, Colour c){
		bitset<hex_count> active_colour = c == white ? bb.Wpieces : bb.Bpieces;
		return (cornerAttacks1(bb.Occupied, pos) | cornerAttacks2(bb.Occupied, pos) | cornerAttacks3(bb.Occupied, pos)) & ~active_colour;
	}
	inline bitset<hex_count> getQueenAttacks(BitBoard &bb, Tile pos, Colour c){
		return getRookAttacks(bb, pos, c) | getBishopAttacks(bb, pos, c);
	}
};
