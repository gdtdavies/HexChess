#pragma once
#include "Enums.h"
#include "Bitboards.h"
#include "LookupBitBoards.h"

#include <iostream>
#include <bitset>
#include <string>


class Move {
private:
	Tile origin;
	Tile destination;
	Type type;
	Colour colour;

	Type takenType = Type::empty;

	bool done = false;

	//bool isEnPassent();
public:
	Move(Tile origin, Tile destination, Type type, Colour colour);

	inline Tile getOrigin() { return origin; }
	inline Tile getDestination() { return destination; }
	inline Type getType() { return type; }
	inline Colour getColour() { return colour; }

	inline void setTakenType(Type ttype) { takenType = ttype; }

	void run(BitBoard &bb);
	void undo(BitBoard &bb);

	bool WisCheck(BitBoard& bb, LookupBitboard& LuBB);
	bool BisCheck(BitBoard& bb, LookupBitboard& LuBB);
	
	bool isLegal(BitBoard &bb, LookupBitboard& LuBB, bitset<115> attacks, Colour c);

	void toString();
	
};