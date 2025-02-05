#pragma once

#include "Enums.h"
#include "Move.h"
#include "Bitboards.h"
#include "LookupBitBoards.h"
#include <bitset>
#include <vector>


class MoveGenerator {
private:

public:
	std::bitset<hex_count> getLegalMoves(BitBoard& bb, LookupBitboard& LuBB, Tile tile, Colour c, Type t, std::vector<Move> move_history);
	std::bitset<hex_count> getLegalCaptures(BitBoard& bb, LookupBitboard& LuBB, Tile tile, Colour c, Type t, std::vector<Move> move_history);
	std::vector<Move> getAllMoves(BitBoard& bb, LookupBitboard& LuBB, std::vector<Move> move_history, bool capturesOnly);
};