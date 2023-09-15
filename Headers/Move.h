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

	Promotion promo = toNone;

	bool done = false;

	int phalfMC = 0, pfullMC = 0;
	bitset<hex_count> pEnPassent = 0;

public:
	inline Move() {}
	Move(Tile origin, Tile destination, Type type, Colour colour);

	inline Tile getOrigin() { return origin; }
	inline Tile getDestination() { return destination; }
	inline Type getType() { return type; }
	inline Colour getColour() { return colour; }
	inline Promotion getPromotion() { return promo; }

	inline void setOrigin(Tile origin) { this->origin = origin; }
	inline void setDestination(Tile destination) { this->destination = destination; }
	inline void setType(Type type) { this->type = type; }
	inline void setColour(Colour colour) { this->colour = colour; }
	inline void setTakenType(Type ttype) { takenType = ttype; }
	inline void setPromotion(Promotion promo) { this->promo = promo; }

	void run(BitBoard& bb, vector<Move>& moves);
	void undo(BitBoard& bb, vector<Move>& moves);

	bool WisCheck(BitBoard& bb, LookupBitboard& LuBB);
	bool BisCheck(BitBoard& bb, LookupBitboard& LuBB);
	
	bool isLegal(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves);

	bool isCheckmate(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves);
	bool isStalemate(BitBoard& bb, LookupBitboard& LuBB, vector<Move>& moves);
	bool isDraw(BitBoard& bb, vector<Move>& moves);

	void print();

	inline bool operator==(Move m) {
		return (origin == m.getOrigin() && destination == m.getDestination() && type == m.getType() && colour == m.getColour());
	}
	
};