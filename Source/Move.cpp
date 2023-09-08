#include "../Headers/Move.h"


Move::Move(Tile origin, Tile destination, Type type, Colour colour)
{
	this->origin = origin;
	this->destination = destination;
	this->type = type;
	this->colour = colour;
}

void Move::run(BitBoard& bb) {
	
	if (colour == white) {
		if (type == pawn) { bb.Wpawns.reset(origin); bb.Wpawns.set(destination); }
		else if (type == knight) { bb.Wknights.reset(origin); bb.Wknights.set(destination); }
		else if (type == bishop) { bb.Wbishops.reset(origin); bb.Wbishops.set(destination); }
		else if (type == rook) { bb.Wrooks.reset(origin); bb.Wrooks.set(destination); }
		else if (type == queen) { bb.Wqueens.reset(origin); bb.Wqueens.set(destination); }
		else if (type == king) { bb.Wking.reset(origin); bb.Wking.set(destination); }
		
	}
	else if (colour == black) {
		if (type == pawn) { bb.Bpawns.reset(origin); bb.Bpawns.set(destination); }
		else if (type == knight) { bb.Bknights.reset(origin); bb.Bknights.set(destination); }
		else if (type == bishop) { bb.Bbishops.reset(origin); bb.Bbishops.set(destination); }
		else if (type == rook) { bb.Brooks.reset(origin); bb.Brooks.set(destination); }
		else if (type == queen) { bb.Bqueens.reset(origin); bb.Bqueens.set(destination); }
		else if (type == king) { bb.Bking.reset(origin); bb.Bking.set(destination); }

	}
	
	if (takenType != Type::empty) {
		if (colour == white) {
			if (takenType == pawn) bb.Bpawns.reset(destination);
			else if (takenType == knight) bb.Bknights.reset(destination);
			else if (takenType == bishop) bb.Bbishops.reset(destination);
			else if (takenType == rook) bb.Brooks.reset(destination);
			else if (takenType == queen) bb.Bqueens.reset(destination);
			else if (takenType == king) bb.Bking.reset(destination);
		}
		else if (colour == black) {
			if (takenType == pawn) bb.Wpawns.reset(destination);
			else if (takenType == knight) bb.Wknights.reset(destination);
			else if (takenType == bishop) bb.Wbishops.reset(destination);
			else if (takenType == rook) bb.Wrooks.reset(destination);
			else if (takenType == queen) bb.Wqueens.reset(destination);
			else if (takenType == king) bb.Wking.reset(destination);
		}
	}
	bb.Wpieces = bb.Wpawns | bb.Wknights | bb.Wbishops | bb.Wrooks | bb.Wqueens | bb.Wking;
	bb.Bpieces = bb.Bpawns | bb.Bknights | bb.Bbishops | bb.Brooks | bb.Bqueens | bb.Bking;

	bb.Occupied = bb.Wpieces | bb.Bpieces;

	done = true;
}

void Move::undo(BitBoard& bb){
	//TODO: implement
	if (!done) return; // don't want to undo a move that hasn't been made yet

	if (colour == white) {
		if (type == pawn) { bb.Wpawns.set(origin); bb.Wpawns.reset(destination); }
		else if (type == knight) { bb.Wknights.set(origin); bb.Wknights.reset(destination); }
		else if (type == bishop) { bb.Wbishops.set(origin); bb.Wbishops.reset(destination); }
		else if (type == rook) { bb.Wrooks.set(origin); bb.Wrooks.reset(destination); }
		else if (type == queen) { bb.Wqueens.set(origin); bb.Wqueens.reset(destination); }
		else if (type == king) { bb.Wking.set(origin); bb.Wking.reset(destination); }

	}
	else if (colour == black) {
		if (type == pawn) { bb.Bpawns.set(origin); bb.Bpawns.reset(destination); }
		else if (type == knight) { bb.Bknights.set(origin); bb.Bknights.reset(destination); }
		else if (type == bishop) { bb.Bbishops.set(origin); bb.Bbishops.reset(destination); }
		else if (type == rook) { bb.Brooks.set(origin); bb.Brooks.reset(destination); }
		else if (type == queen) { bb.Bqueens.set(origin); bb.Bqueens.reset(destination); }
		else if (type == king) { bb.Bking.set(origin); bb.Bking.reset(destination); }

	}

	if (takenType != Type::empty) {
		if (colour == white) {
			if (takenType == pawn) bb.Bpawns.set(destination);
			else if (takenType == knight) bb.Bknights.set(destination);
			else if (takenType == bishop) bb.Bbishops.set(destination);
			else if (takenType == rook) bb.Brooks.set(destination);
			else if (takenType == queen) bb.Bqueens.set(destination);
			else if (takenType == king) bb.Bking.set(destination);
		}
		else if (colour == black) {
			if (takenType == pawn) bb.Wpawns.set(destination);
			else if (takenType == knight) bb.Wknights.set(destination);
			else if (takenType == bishop) bb.Wbishops.set(destination);
			else if (takenType == rook) bb.Wrooks.set(destination);
			else if (takenType == queen) bb.Wqueens.set(destination);
			else if (takenType == king) bb.Wking.set(destination);
		}
	}
	bb.Wpieces = bb.Wpawns | bb.Wknights | bb.Wbishops | bb.Wrooks | bb.Wqueens | bb.Wking;
	bb.Bpieces = bb.Bpawns | bb.Bknights | bb.Bbishops | bb.Brooks | bb.Bqueens | bb.Bking;

	bb.Occupied = bb.Wpieces | bb.Bpieces;

	done = false;
}

bool Move::WisCheck(BitBoard& bb, LookupBitboard& LuBB) {
	for (int hex = 0; hex < hex_count; hex++) {

		if (bb.SkipHexes.test(hex)) continue;
		if (!bb.Bpieces.test(hex))continue;

		for (int attack = 0; attack < hex_count; attack++) {
			if (bb.SkipHexes.test(attack)) continue;
			if (!bb.Wking.test(attack)) continue;

			if (bb.Bpawns.test(hex)   && (LuBB.getPawnMoves    (bb, (Tile)hex, black) | LuBB.getPawnAttacks(bb, (Tile)hex, black)).test(attack)) return true;
			if (bb.Bknights.test(hex) && LuBB.getKnightAttacks(bb, (Tile)hex, black).test(attack)) return true;
			if (bb.Bbishops.test(hex) && LuBB.getBishopAttacks(bb, (Tile)hex, black).test(attack)) return true;
			if (bb.Brooks.test(hex)   && LuBB.getRookAttacks  (bb, (Tile)hex, black).test(attack)) return true;
			if (bb.Bqueens.test(hex)  && LuBB.getQueenAttacks (bb, (Tile)hex, black).test(attack)) return true;
			if (bb.Bking.test(hex)    && LuBB.getKingAttacks  (bb, (Tile)hex, black).test(attack)) return true;
		}
	}
	return false;
}

bool Move::BisCheck(BitBoard& bb, LookupBitboard& LuBB) {
	for (int hex = 0; hex < hex_count; hex++) {

		if (bb.SkipHexes.test(hex)) continue;
		if (!bb.Wpieces.test(hex))continue;

		for (int attack = 0; attack < hex_count; attack++) {
			if (bb.SkipHexes.test(attack)) continue;
			if (!bb.Bking.test(attack)) continue;

			if (bb.Wpawns.test(hex)   && (LuBB.getPawnMoves   (bb, (Tile)hex, white) | LuBB.getPawnAttacks(bb, (Tile)hex, white)).test(attack)) return true;
			if (bb.Wknights.test(hex) && LuBB.getKnightAttacks(bb, (Tile)hex, white).test(attack)) return true;
			if (bb.Wbishops.test(hex) && LuBB.getBishopAttacks(bb, (Tile)hex, white).test(attack)) return true;
			if (bb.Wrooks.test(hex)   && LuBB.getRookAttacks  (bb, (Tile)hex, white).test(attack)) return true;
			if (bb.Wqueens.test(hex)  && LuBB.getQueenAttacks (bb, (Tile)hex, white).test(attack)) return true;
			if (bb.Wking.test(hex)    && LuBB.getKingAttacks  (bb, (Tile)hex, white).test(attack)) return true;
		}
	}
	return false;
}

bool Move::isLegal(BitBoard& bb, LookupBitboard& LuBB) {
	//check the move is in the list of moves for the piece
	bitset<hex_count> attacks
		= type == pawn ? (LuBB.getPawnAttacks(bb, origin, colour) | LuBB.getPawnMoves(bb, origin, colour))
		: type == knight ? LuBB.getKnightAttacks(bb, origin, colour)
		: type == bishop ? LuBB.getBishopAttacks(bb, origin, colour)
		: type == rook ? LuBB.getRookAttacks(bb, origin, colour)
		: type == queen ? LuBB.getQueenAttacks(bb, origin, colour)
		: type == king ? LuBB.getKingAttacks(bb, origin, colour)
		: 0;
	if (!attacks.test(destination)) return false;
	//if the piece is a pawn, check that their isn't a piece blocking the double move
	if (colour == white && bb.WpawnStarts.test(origin) && bb.Occupied.test(origin + 1)) return false;
	if (colour == black && bb.BpawnStarts.test(origin) && bb.Occupied.test(origin - 1)) return false;
	//make the move
	this->run(bb);
	//check if the move puts the player in check
	bool isLegal = true;
	if      (colour == white && this->WisCheck(bb, LuBB)) isLegal = false;
	else if (colour == black && this->BisCheck(bb, LuBB)) isLegal = false;
	//undo the move
	this->undo(bb);
	//if it did put the player in check, return false
	return isLegal;
}

bool Move::isCheckmate(BitBoard& bb, LookupBitboard& LuBB) {
	//check if the move puts the other player in check
	if (colour == white && !this->BisCheck(bb, LuBB)) return false;
	if (colour == black && !this->WisCheck(bb, LuBB)) return false;

	for (int hex = 0; hex < hex_count; hex++) {
		if (bb.SkipHexes.test(hex)) continue;
		if (colour == white && !bb.Bpieces.test(hex)) continue;
		if (colour == black && !bb.Wpieces.test(hex)) continue;

		for (int attack = 0; attack < hex_count; attack++) {
			if (bb.SkipHexes.test(attack)) continue;
			
			Move m = Move((Tile)hex, (Tile)attack, bb.getTypeInHex((Tile)hex), colour == white ? black : white);
			m.setTakenType(bb.getTypeInHex((Tile)attack));

			//it is not checkmate if a legal move exists
			if (m.isLegal(bb, LuBB))
				return false;
		}
	}
	return true;
}

void Move::toString() {
	cout << "move: \n\torigin = " << origin << "\n\tdestination = " << destination << "\n\ttype = " << type << "\n\ttakenType = " << takenType <<  "\n\tcolour = " << colour << endl;
}