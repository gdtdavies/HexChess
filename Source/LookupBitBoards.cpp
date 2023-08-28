#include "../Headers/LookupBitboards.h"

#include<vector>

//-----------------------------------------------------------------------------
//-private methods-------------------------------------------------------------
//-----------------------------------------------------------------------------

//bool LookupBitboard::isNegative(int dir){}
//int LookupBitboard::bitScan(bitset<92> mask, bool isNegative){}
//bitset<92> LookupBitboard::getRayAttacks(bitset<92> occupied, Direction dir, Tile hex){}
//
//bitset<92> LookupBitboard::cornerAttacks1(bitset<92> occupied, Tile hex){}
//bitset<92> LookupBitboard::cornerAttacks2(bitset<92> occupied, Tile hex){}
//bitset<92> LookupBitboard::cornerAttacks3(bitset<92> occupied, Tile hex){}
//
//bitset<92> LookupBitboard::edgeAttacks1(bitset<92> occupied, Tile hex){}
//bitset<92> LookupBitboard::edgeAttacks2(bitset<92> occupied, Tile hex){}
//bitset<92> LookupBitboard::edgeAttacks3(bitset<92> occupied, Tile hex){}

//-----------------------------------------------------------------------------
//-public methods-------------------------------------------------------------
//-----------------------------------------------------------------------------


void LookupBitboard::setPawnMoves() {
	vector<int> Wskips = { 2, 3, 4, 5, 9, 10, 11, 12, 17, 18, 19, 20, 26, 27, 28, 29, 40, 51, 61, 70, 78 };
	vector<int> Wstart = { 1, 8, 16, 25, 35, 36, 37, 38, 39 };

	vector<int> Bskips = { 12, 20, 29, 39, 50, 61, 62, 63, 64, 70, 71, 72, 73, 78, 79, 81, 85, 86, 87, 88 };
	vector<int> Bstart = { 51, 52, 53, 54, 55, 65, 74, 82, 89 };

	int Wmove = 6;
	int Bmove = 6;
	for (int i = 0; i < 91; i++) {
		if (i == 6 || i == 13 || i == 21 || i == 30) Wmove++;
		if (i == 51 || i == 61 || i == 70 || i == 78) Wmove--;
		if (i == 13 || i == 21 || i == 30 || i == 40) Bmove++;
		if (i == 61 || i == 70 || i == 78 || i == 85) Bmove--;

		//white pawns
		if (i < 85 && count(Wskips.begin(), Wskips.end(), i) == 0) {
			WpawnMoves[i].set(i + Wmove);
			if (count(Wstart.begin(), Wstart.end(), i) > 0) {
				int extra = i < 35 ? Wmove * 2 + 1 : Wmove * 2;
				WpawnMoves[i].set(i + extra);
			}
		}
		//black pawns
		if (i > 5 && count(Bskips.begin(), Bskips.end(), i) == 0) {
			BpawnMoves[i].set(i - Bmove);
			if (count(Bstart.begin(), Bstart.end(), i) > 0) {
				int extra = i > 55 ? Bmove * 2 + 1 : Bmove * 2;
				BpawnMoves[i].set(i - extra);
			}
		}
	}
}
bitset<92> LookupBitboard::getPawnMoves(Tile pos, Colour c) {
	return c == white ? WpawnMoves[pos] : BpawnMoves[pos];
}

void LookupBitboard::setPawnAttacks() {
	vector<int> WleftFile = { 0, 6, 13, 21, 30, 40, 51, 61, 70, 78, 85 };
	vector<int> WrightFile = { 50, 60, 69, 77, 84, 90, 89, 88, 87, 86, 85 };

	vector<int> BleftFile = {5, 4, 3, 2, 1, 0, 6, 13, 21, 30, 40};
	vector<int> BrightFile = {5, 12, 20, 29, 39, 50, 60, 69, 77, 84, 90};

	vector<int> Wskips = { 2, 3, 4, 5, 9, 10, 11, 12, 17, 18, 19, 20, 26, 27, 28, 29, 40, 51, 61, 70, 78 };
	vector<int> Bskips = { 12, 20, 29, 39, 50, 61, 62, 63, 64, 70, 71, 72, 73, 78, 79, 81, 85, 86, 87, 88 };


	int Wmove = 7;
	int Bmove = 7;
	for (int i = 0; i < 91; i++) {
		if (i == 6 || i == 13 || i == 21 || i == 30) Wmove++;
		if (i == 51 || i == 61 || i == 70 || i == 78) Wmove--;
		if (i == 13 || i == 21 || i == 30 || i == 40) Bmove++;
		if (i == 61 || i == 70 || i == 78 || i == 85) Bmove--;

		if (i < 85 && count(Wskips.begin(), Wskips.end(), i) == 0) {
			if (count(WleftFile.begin(), WleftFile.end(), i) == 0) 
				WpawnAttacks[i].set(i - 1);
			if (count(WrightFile.begin(), WrightFile.end(), i) == 0) 
				WpawnAttacks[i].set(i + Wmove);
		}

		if (i > 5 && count(Bskips.begin(), Bskips.end(), i) == 0) {
			if (count(BleftFile.begin(), BleftFile.end(), i) == 0)
				BpawnAttacks[i].set(i - Bmove);
			if (count(BrightFile.begin(), BrightFile.end(), i) == 0)
				BpawnAttacks[i].set(i + 1);
		}

	}
}

	
	

bitset<92> LookupBitboard::getPawnAttacks(Tile pos, Colour c) {
	return c == white ? WpawnAttacks[pos] : BpawnAttacks[pos];
}

//void LookupBitboard::setKnightAttacks(){}
//bitset<92> LookupBitboard::getKnightAttacks(Tile pos, Colour c){}
//
//void LookupBitboard::setKingAttacks(){}
//bitset<92> LookupBitboard::getKingAttacks(Tile pos, Colour c){}
//
//void LookupBitboard::setRayAttacks(){}
//bitset<92> LookupBitboard::getRookAttacks(Tile pos, Colour c){}
//bitset<92> LookupBitboard::getBishopAttacks(Tile pos, Colour c){}
//bitset<92> LookupBitboard::getQueenAttacks(Tile pos, Colour c){}