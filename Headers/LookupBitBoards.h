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

	bitset<hex_count> cornerAttacks1(bitset<hex_count> occupied, Tile hex);
	bitset<hex_count> cornerAttacks2(bitset<hex_count> occupied, Tile hex);
	bitset<hex_count> cornerAttacks3(bitset<hex_count> occupied, Tile hex);
	
	bitset<hex_count> edgeAttacks1(bitset<hex_count> occupied, Tile hex);
	bitset<hex_count> edgeAttacks2(bitset<hex_count> occupied, Tile hex);
	bitset<hex_count> edgeAttacks3(bitset<hex_count> occupied, Tile hex);

public:
	void setPawnAttacks(BitBoard& bb);
	void setPawnMoves(BitBoard& bb);
	void setKnightAttacks(BitBoard& bb);
	void setKingAttacks(BitBoard& bb);
	void setRayAttacks(BitBoard& bb);

	bitset<hex_count> getPawnAttacks(BitBoard& bb, Tile pos, Colour c);
	bitset<hex_count> getPawnMoves(BitBoard& bb, Tile pos, Colour c);
	bitset<hex_count> getKnightAttacks(BitBoard& bb, Tile pos);
	bitset<hex_count> getKingAttacks(BitBoard& bb, Tile pos);
	bitset<hex_count> getRookAttacks(BitBoard &bb, Tile pos);
	bitset<hex_count> getBishopAttacks(BitBoard &bb, Tile pos);
	bitset<hex_count> getQueenAttacks(BitBoard &bb, Tile pos);
};
