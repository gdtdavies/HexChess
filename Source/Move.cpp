#include "../Headers/Move.h"

//-----------------------------------------------------------------------------
//-private methods-------------------------------------------------------------
//-----------------------------------------------------------------------------

//no private methods yet

//-----------------------------------------------------------------------------
//-public methods--------------------------------------------------------------
//-----------------------------------------------------------------------------

Move::Move(Tile origin, Tile destination, Type type, Colour colour)
{
	this->origin = origin;
	this->destination = destination;
	this->type = type;
	this->colour = colour;
}

void Move::run(BitBoard& bb, vector<Move>& moves) {
	phalfMC = bb.halfMC;
	pfullMC = bb.fullMC;
	
	pEnPassent = bb.EnPassents;
	
	
	if (colour == white) {
		if (type == pawn) { 
			bb.Wpawns.reset(origin); bb.Wpawns.set(destination); 
			if (bb.EnPassents.test(destination)) {
				if      (destination == origin + EdgeNW)  bb.Bpawns.reset(destination + EdgeS);
				else if (destination == origin + EdgeNE)  bb.Bpawns.reset(destination + EdgeS);
			}
			bb.EnPassents = 0;
			if (destination == origin + 2*EdgeN)
				bb.EnPassents.set(origin + EdgeN);
			if (promo != toNone) {
				bb.Wpawns.reset(destination);
				if (promo == toKnight) bb.Wknights.set(destination);
				else if (promo == toBishop) bb.Wbishops.set(destination);
				else if (promo == toRook) bb.Wrooks.set(destination); 
				else if (promo == toQueen) bb.Wqueens.set(destination);
			}
			bb.halfMC = -1;
		}
		else if (type == knight) { bb.Wknights.reset(origin); bb.Wknights.set(destination); }
		else if (type == bishop) { bb.Wbishops.reset(origin); bb.Wbishops.set(destination); }
		else if (type == rook) { bb.Wrooks.reset(origin); bb.Wrooks.set(destination); }
		else if (type == queen) { bb.Wqueens.reset(origin); bb.Wqueens.set(destination); }
		else if (type == king) { bb.Wking.reset(origin); bb.Wking.set(destination); }
		
	}
	else if (colour == black) {
		if (type == pawn) { 
			bb.Bpawns.reset(origin); bb.Bpawns.set(destination);
			if (bb.EnPassents.test(destination)) {
				if      (destination == origin + EdgeSW)  bb.Wpawns.reset(destination + EdgeN);
				else if (destination == origin + EdgeSE)  bb.Wpawns.reset(destination + EdgeN);
			}
			bb.EnPassents = 0;
			if (destination == origin + 2 * EdgeS)
				bb.EnPassents.set(origin + EdgeS);
			if (promo != toNone) {
				bb.Bpawns.reset(destination);
				if (promo == toKnight) bb.Bknights.set(destination);
				else if (promo == toBishop) bb.Bbishops.set(destination);
				else if (promo == toRook) bb.Brooks.set(destination);
				else if (promo == toQueen) bb.Bqueens.set(destination);
			}
			bb.halfMC = -1;
		}
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
		
		bb.halfMC = -1;
	}
	bb.Wpieces = bb.Wpawns | bb.Wknights | bb.Wbishops | bb.Wrooks | bb.Wqueens | bb.Wking;
	bb.Bpieces = bb.Bpawns | bb.Bknights | bb.Bbishops | bb.Brooks | bb.Bqueens | bb.Bking;

	bb.Occupied = bb.Wpieces | bb.Bpieces;

	if (type != pawn) bb.EnPassents = 0;

	bb.halfMC++;
	if (colour == black)
		bb.fullMC++;

	moves.push_back(*this);

	done = true;
}

void Move::undo(BitBoard& bb, vector<Move>& moves){
	if (!done) return; // don't want to undo a move that hasn't been made yet
	
	bb.halfMC = phalfMC;
	bb.fullMC = pfullMC;

	bb.EnPassents = pEnPassent;

	if (colour == white) {
		if (type == pawn)   { 
			bb.Wpawns.set(origin);   bb.Wpawns.reset(destination);  
			if (pEnPassent.test(destination))
				bb.Bpawns.set(destination + EdgeS);
			if (promo != toNone) {
				if (promo == toKnight) bb.Wknights.reset(destination);
				else if (promo == toBishop) bb.Wbishops.reset(destination);
				else if (promo == toRook) bb.Wrooks.reset(destination);
				else if (promo == toQueen) bb.Wqueens.reset(destination);
			}
		}
		else if (type == knight) { bb.Wknights.set(origin); bb.Wknights.reset(destination); }
		else if (type == bishop) { bb.Wbishops.set(origin); bb.Wbishops.reset(destination); }
		else if (type == rook)   { bb.Wrooks.set(origin);   bb.Wrooks.reset(destination);   }
		else if (type == queen)  { bb.Wqueens.set(origin);  bb.Wqueens.reset(destination);  }
		else if (type == king)   { bb.Wking.set(origin);    bb.Wking.reset(destination);    }

	}
	else if (colour == black) {
		if (type == pawn)   {
			bb.Bpawns.set(origin); bb.Bpawns.reset(destination);
			if (pEnPassent.test(destination))
				bb.Wpawns.set(destination + EdgeN);
			if (promo != toNone) {
				if (promo == toKnight) bb.Bknights.reset(destination);
				else if (promo == toBishop) bb.Bbishops.reset(destination);
				else if (promo == toRook) bb.Brooks.reset(destination);
				else if (promo == toQueen) bb.Bqueens.reset(destination);
			}
		}
		else if (type == knight) { bb.Bknights.set(origin); bb.Bknights.reset(destination); }
		else if (type == bishop) { bb.Bbishops.set(origin); bb.Bbishops.reset(destination); }
		else if (type == rook)   { bb.Brooks.set(origin); bb.Brooks.reset(destination); }
		else if (type == queen)  { bb.Bqueens.set(origin); bb.Bqueens.reset(destination); }
		else if (type == king)   { bb.Bking.set(origin); bb.Bking.reset(destination); }

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
	moves.pop_back();
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
			if (bb.Bknights.test(hex) && LuBB.getKnightAttacks(bb, (Tile)hex).test(attack)) return true;
			if (bb.Bbishops.test(hex) && LuBB.getBishopAttacks(bb, (Tile)hex).test(attack)) return true;
			if (bb.Brooks.test(hex)   && LuBB.getRookAttacks  (bb, (Tile)hex).test(attack)) return true;
			if (bb.Bqueens.test(hex)  && LuBB.getQueenAttacks (bb, (Tile)hex).test(attack)) return true;
			if (bb.Bking.test(hex)    && LuBB.getKingAttacks  (bb, (Tile)hex).test(attack)) return true;
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
			if (bb.Wknights.test(hex) && LuBB.getKnightAttacks(bb, (Tile)hex).test(attack)) return true;
			if (bb.Wbishops.test(hex) && LuBB.getBishopAttacks(bb, (Tile)hex).test(attack)) return true;
			if (bb.Wrooks.test(hex)   && LuBB.getRookAttacks  (bb, (Tile)hex).test(attack)) return true;
			if (bb.Wqueens.test(hex)  && LuBB.getQueenAttacks (bb, (Tile)hex).test(attack)) return true;
			if (bb.Wking.test(hex)    && LuBB.getKingAttacks  (bb, (Tile)hex).test(attack)) return true;
		}
	}
	return false;
}

bool Move::isLegal(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves) {
	//check the move is in the list of moves for the piece
	bitset<hex_count> opponant_pieces = colour == white ? bb.Bpieces : bb.Wpieces;
	bitset<hex_count> active_pieces = bb.Occupied & ~opponant_pieces;
	
	bitset<hex_count> attacks
		= type == pawn ? ((LuBB.getPawnAttacks(bb, origin, colour) & opponant_pieces) | LuBB.getPawnMoves(bb, origin, colour) & ~bb.Occupied | (bb.EnPassents & LuBB.getPawnAttacks(bb, origin, colour)))
		: type == knight ? LuBB.getKnightAttacks(bb, origin) & ~active_pieces
		: type == bishop ? LuBB.getBishopAttacks(bb, origin) & ~active_pieces
		: type == rook ? LuBB.getRookAttacks(bb, origin) & ~active_pieces
		: type == queen ? LuBB.getQueenAttacks(bb, origin) & ~active_pieces
		: type == king ? LuBB.getKingAttacks(bb, origin) & ~active_pieces
		: 0;
	if (!attacks.test(destination)) return false;
	//if the piece is a pawn, check that their isn't a piece blocking the double move
	if (colour == white && bb.WpawnStarts.test(origin) && bb.Occupied.test(origin + EdgeN)) return false;
	if (colour == black && bb.BpawnStarts.test(origin) && bb.Occupied.test(origin + EdgeS)) return false;
	//make the move
	this->run(bb, moves);
	//check if the move puts the player in check
	bool isLegal = true;
	if      (colour == white && this->WisCheck(bb, LuBB)) isLegal = false;
	else if (colour == black && this->BisCheck(bb, LuBB)) isLegal = false;
	//undo the move
	this->undo(bb, moves);
	//if it did put the player in check, return false
	return isLegal;
}

bool Move::isCheckmate(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves) {
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
			if (m.isLegal(bb, LuBB, moves))
				return false;
		}
	}
	return true;
}

bool Move::isStalemate(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves) {
	//check if the move puts the other player in check. it can't be stalemate if the other player is in check
	if (colour == white && this->BisCheck(bb, LuBB)) return false;
	if (colour == black && this->WisCheck(bb, LuBB)) return false;

	for (int hex = 0; hex < hex_count; hex++) {
		if (bb.SkipHexes.test(hex)) continue;
		if (colour == white && !bb.Bpieces.test(hex)) continue;
		if (colour == black && !bb.Wpieces.test(hex)) continue;

		for (int attack = 0; attack < hex_count; attack++) {
			if (bb.SkipHexes.test(attack)) continue;

			Move m = Move((Tile)hex, (Tile)attack, bb.getTypeInHex((Tile)hex), colour == white ? black : white);
			m.setTakenType(bb.getTypeInHex((Tile)attack));

			//it is not stalemate if a legal move exists
			if (m.isLegal(bb, LuBB, moves))
				return false;
		}
	}
	return true;
}

bool Move::isDraw(BitBoard& bb, vector<Move>& moves) {
	//50 move rule
	if (bb.halfMC >= 100) {
		cout << "move clock exceeded" << endl;
		return true;
	}
	//insufficient material
	if ((bb.Wqueens | bb.Bqueens).none() && (bb.Wrooks | bb.Brooks).none() && (bb.Wpawns | bb.Bpawns).none()) {
		if (bb.Wbishops.count() <= 1 && bb.Bbishops.count() <= 1 && bb.Wknights.count() <= 1 && bb.Bknights.count() <= 1) {
			if ((bb.Wbishops | bb.Wknights).count() <= 1 && (bb.Bbishops | bb.Bknights).count() <= 1) {
				cout << "insufficient material" << endl;
				return true;
			}
		}
	}
	//3 fold repetition
	return false;
}

void Move::print() {
	cout << "move: \n\torigin = " << origin << "\n\tdestination = " << destination << "\n\ttype = " << type << "\n\ttakenType = " << takenType <<  "\n\tcolour = " << colour << endl;
}