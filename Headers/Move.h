#pragma once
#include "Enums.h"
#include "Bitboards.h"
#include "LookupBitBoards.h"

#include <iostream>
#include <bitset>
#include <string>


class Move {
private:
	Tile origin = (Tile)0;
	Tile destination = (Tile)0;
	Type type = Type::empty;
	Colour colour = Colour::NA;

	Type takenType = Type::empty;

	bool done = false;

	int phalfMC = 0, pfullMC = 0;
	bitset<hex_count> pEnPassent = 0;

	//bool isEnPassent();
public:
	inline Move() {}
	Move(Tile origin, Tile destination, Type type, Colour colour);

	inline Tile getOrigin() { return origin; }
	inline Tile getDestination() { return destination; }
	inline Type getType() { return type; }
	inline Colour getColour() { return colour; }

	inline void setOrigin(Tile origin) { this->origin = origin; }
	inline void setDestination(Tile destination) { this->destination = destination; }
	inline void setType(Type type) { this->type = type; }
	inline void setColour(Colour colour) { this->colour = colour; }
	inline void setTakenType(Type ttype) { takenType = ttype; }

	void run(BitBoard& bb);
	void undo(BitBoard& bb);

	bool WisCheck(BitBoard& bb, LookupBitboard& LuBB);
	bool BisCheck(BitBoard& bb, LookupBitboard& LuBB);
	
	bool isLegal(BitBoard& bb, LookupBitboard& LuBB);

	bool isCheckmate(BitBoard& bb, LookupBitboard& LuBB);
	bool isStalemate(BitBoard& bb, LookupBitboard& LuBB);
	bool isDraw(BitBoard& bb);

	void toString();
	
};