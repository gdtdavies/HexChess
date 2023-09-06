#include "../Headers/Move.h"


Move::Move(Tile origin, Tile destination, Type type, Colour colour)
{
	this->origin = origin;
	this->destination = destination;
	this->type = type;
	this->colour = colour;
}

void Move::run(BitBoard &bb) {
	
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

void Move::undo(BitBoard &bb){
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

bool Move::isLegal(BitBoard &bb, bitset<115> attacks) {
	//check the move is in the list of moves for the piece
	if (!attacks.test(destination)) return false;
	//chec the destination is on occupied by a friendly piece
	bitset<115> active_colour = (colour == white) ? bb.Wpieces : (colour == black) ? bb.Bpieces : 0;
	if (active_colour.test(destination)) return false;
	//make the move
	//check if the move puts the player in check
	//undo the move
	//if it did put the player in check, return false
	return true;
}

void Move::toString() {
	cout << "move: \n\torigin = " << origin << "\n\tdestination = " << destination << "\n\ttype = " << type << "\n\ttakenType = " << takenType <<  "\n\tcolour = " << colour << endl;
}