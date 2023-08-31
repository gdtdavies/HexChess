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


void LookupBitboard::setKnightAttacks() {
	vector<int> file1      = { 0,  6, 13, 21, 30, 40, 51, 61, 70, 78, 85 };
	vector<int> file1_rank = { 0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5 };
	vector<int> rankEnds   = { 5, 12, 20, 29, 39, 50, 60, 69, 77, 84, 90 };

	for (int i = 0; i < 91; i++) {
		vector<int> attacks;

		int rank = -1;
		for (int f : file1) {
			if (i >= f) rank++;
		}

		int temp = i;
		while (count(file1.begin(), file1.end(), temp) == 0)
			temp--;
		int file = i - temp + file1_rank[rank];
		
		// SW SW NW = rank - 2 & file - 3
		if (rank >= 2 && file >= 3) {
			if (!(file - file1_rank[rank] == 0 && i >= 70)) {
				int new_rank = rank - 2;
				int new_file = file - 3 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// NW NW SW = rank - 1 & file - 3
		if (rank >= 1 && file >= 3) {
			if (!(file - file1_rank[rank] == 0 && i >= 70) &&
				 !(file - file1_rank[rank] == 1 && i >= 62)) {
				int new_rank = rank - 1;
				int new_file = file - 3 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// NW NW N  = rank + 1 & file - 2
		if (rank <= 10 - 1 && file >= 2) {
			if (!(file - file1_rank[rank] == 0 && i >= 61) &&
				 !(file - file1_rank[rank] == 1 && i >= 52) &&
				 !(file - file1_rank[rank] == 2 && i >= 42)) {
				int new_rank = rank + 1;
				int new_file = file - 2 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// N N NW   = rank + 2 & file - 1
		if (rank <= 10 - 2 && file >= 1) {
			if (!(file - file1_rank[rank] == 0 && i >= 51) &&
				 !(file - file1_rank[rank] == 1 && i >= 41) &&
				 !(file - file1_rank[rank] == 2 && i >= 42)) {
				int new_rank = rank + 2;
				int new_file = file - 1 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// N N NE   = rank + 3 & file + 1
		if (rank <= 10 - 3 && file <= 10 - 1) {
			if (!(file - file1_rank[rank] == 0 && i >= 30) &&
				 !(file - file1_rank[rank] == 1 && i >= 31) &&
				 !(file - file1_rank[rank] == 2 && i >= 42)) {
				int new_rank = rank + 3;
				int new_file = file + 1 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// NE NE N  = rank + 3 & file + 2
		if (rank <= 10 - 3 && file <= 10 - 2) {
			if (!(file - file1_rank[rank] == 0 && i >= 40)) {
				int new_rank = rank + 3;
				int new_file = file + 2 - file1_rank[new_rank];
				int new_i = file1[new_rank] + new_file;

				if (new_i <= rankEnds[new_rank])
					attacks.push_back(new_i);
			}
		}
		// NE NE SE = rank + 2 & file + 3
		if (rank <= 10 - 2 && file <= 10 - 3) {
			int new_rank = rank + 2;
			int new_file = file + 3 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}
		// SE SE NE = rank + 1 & file + 3
		if (rank <= 10 - 1 && file <= 10 - 3) {
			int new_rank = rank + 1;
			int new_file = file + 3 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}
		// SE SE S  = rank - 1 & file + 2
		if (rank >= 1 && file <= 10 - 2) {
			int new_rank = rank - 1;
			int new_file = file + 2 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}
		// S S SE   = rank - 2 & file + 1
		if (rank >= 2 && file <= 10 - 1) {
			int new_rank = rank - 2;
			int new_file = file + 1 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}
		// S S SW   = rank - 3 & file - 1
		if (rank >= 3 && file >= 1) {
			int new_rank = rank - 3;
			int new_file = file - 1 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}
		// SW SW S  = rank - 3 & file - 2
		if (rank >= 3 && file >= 2) {
			int new_rank = rank - 3;
			int new_file = file - 2 - file1_rank[new_rank];
			int new_i = file1[new_rank] + new_file;

			if (new_i <= rankEnds[new_rank])
				attacks.push_back(new_i);
		}

		for (int attack : attacks)
			knightAttacks[i].set(attack);
	}
}

bitset<92> LookupBitboard::getKnightAttacks(Tile pos){
	return knightAttacks[pos];
}

//void LookupBitboard::setKingAttacks(){}
//bitset<92> LookupBitboard::getKingAttacks(Tile pos){}
//
//void LookupBitboard::setRayAttacks(){}
//bitset<92> LookupBitboard::getRookAttacks(Tile pos){}
//bitset<92> LookupBitboard::getBishopAttacks(Tile pos){}
//bitset<92> LookupBitboard::getQueenAttacks(Tile pos){}