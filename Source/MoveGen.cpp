#include "../Headers/MoveGen.h"

std::bitset<hex_count> MoveGenerator::getLegalMoves(BitBoard& bb, LookupBitboard& LuBB, Tile tile, Colour c, Type t, std::vector<Move> move_history) {
	std::bitset<hex_count> moves(0);
	for (int dest = 0; dest < hex_count; dest++) {
		if (bb.SkipHexes.test(dest)) continue;
		if (bb.Occupied.test(dest)) continue;
		Move m = Move(tile, (Tile)dest, t, c);
		if (m.isLegal(bb, LuBB, move_history)) {
			moves.set(dest, 1);
		}
	}
	return moves;
}

std::bitset<hex_count> MoveGenerator::getLegalCaptures(BitBoard& bb, LookupBitboard& LuBB,  Tile tile, Colour c, Type t, std::vector<Move> move_history) {
	std::bitset<hex_count> moves(0);
	for (int dest = 0; dest < hex_count; dest++) {
		if (bb.SkipHexes.test(dest)) continue;
		if (!bb.Occupied.test(dest)) continue;
		Move m = Move(tile, (Tile)dest, t, c);
		if (m.isLegal(bb, LuBB, move_history)) {
			moves.set(dest, 1);
		}
	}
	return moves;
}

std::vector<Move> MoveGenerator::getAllMoves(BitBoard& bb, LookupBitboard& LuBB, std::vector<Move> move_history, bool capturesOnly=false) {
	std::vector<Move> moves;
	for (int origin = 0; origin < hex_count; origin++) {
		if (bb.SkipHexes.test(origin)) continue;
		std::bitset<hex_count> legal_captures = getLegalCaptures(bb, LuBB, (Tile)origin, bb.getColourInHex((Tile)origin), bb.getTypeInHex((Tile)origin), move_history);
		std::bitset<hex_count> legal_moves = getLegalCaptures(bb, LuBB, (Tile)origin, bb.getColourInHex((Tile)origin), bb.getTypeInHex((Tile)origin), move_history);
		for (int dest = 0; dest < hex_count; dest++) {
			if (legal_captures.test(dest)) {
				Move m = Move((Tile)origin, (Tile)dest, bb.getTypeInHex((Tile)origin), bb.getColourInHex((Tile)origin));
				m.setTakenType(bb.getTypeInHex((Tile)dest));
				moves.push_back(m);
			}
			else if (!capturesOnly && legal_moves.test(dest)) {
				Move m = Move((Tile)origin, (Tile)dest, bb.getTypeInHex((Tile)origin), bb.getColourInHex((Tile)origin));
				moves.push_back(m);
			}
		}
	}
	return moves;
}
