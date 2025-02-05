#pragma once

#include "Bitboards.h"
#include "Move.h"


class Evaluator {
private:
	int rootDepth = 0;
	Move bestMove;
	std::vector<float> rootScores;
	std::vector<Move> firstMoves;

	float getPieceMobility(BitBoard& bb);

public:
	double evaluate(BitBoard& bb, LookupBitboard& LuBB, std::vector<Move> move_history, int depth);
	void reset();
};