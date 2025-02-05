#include "../Headers/Eval.h"

double Evaluator::evaluate(BitBoard& bb, LookupBitboard& LuBB, std::vector<Move> move_history, int depth) {
	cout << "evaluating" << endl;
	Move lastMove = move_history.back();

	if (lastMove.isStalemate(bb, LuBB, move_history)) return 0;
	cout << "evaluating2" << endl;
	if (lastMove.isCheckmate(bb, LuBB, move_history)) return -10000 - depth;
	

	//int turn = lastMove.getColour() == white ? 1 : -1;
	float material 
		= 9.00f * (int)(bb.Wqueens.count() - bb.Bqueens.count())
		+ 5.00f * (int)(bb.Wrooks.count() - bb.Brooks.count())
		+ 3.00f * (int)(bb.Wbishops.count() - bb.Bbishops.count())
		+ 3.00f * (int)(bb.Wknights.count() - bb.Bknights.count())
		+ 1.00f * (int)(bb.Wpawns.count() - bb.Bpawns.count());
	
	double score = material;
	cout << "inner score: " << score << endl;

	return score;// *turn;
}

void Evaluator::reset() {
	rootDepth = 0;
	rootScores.clear();
	firstMoves.clear();
}