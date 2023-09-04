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

	std::cout << "Wpieces: " << bb.Wpieces << endl;
	std::cout << "Bpieces: " << bb.Bpieces << endl;
		
}

void Move::undo(){
	//TODO: implement
}

bool Move::isLegal() {
	//check the move is in the list of moves for the piece
	//make the move
	//check if the move puts the player in check
	//undo the move
	//if it did put the player in check, return false
	return true;
}

void Move::toString() {
	cout << "move: \n\torigin = " << origin << "\n\tdestination = " << destination << "\n\ttype = " << type << "\n\ttakenType = " << takenType <<  "\n\tcolour = " << colour << endl;
}