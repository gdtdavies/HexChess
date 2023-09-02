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
	bitset<115> skipHexes("1100000011110000000111000000001100000000010000000000000000000000000000000100000000011000000001110000000111100000011");
	bitset<115> top      ("0010000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000010000000");
	bitset<115> bottom   ("0000000100000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000100");
	
	std::bitset<115> WpawnStart("0000000000000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000000");
	std::bitset<115> BpawnStart("0000000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000000000000");

	for (int i = 0; i < 115; i++) {
		if (skipHexes.test(i)) continue;
		if (!top.test(i)) {
			WpawnAttacks[i].set(i + 1);
			if (WpawnStart.test(i)) 
				WpawnMoves[i].set(i + 2);
		}
		if (!bottom.test(i)) {
			BpawnAttacks[i].set(i - 1);
			if (BpawnStart.test(i))
				BpawnMoves[i].set(i - 2);
		}
	}
	
}
void LookupBitboard::setPawnAttacks() {
	bitset<115> skipHexes("1100000011110000000111000000001100000000010000000000000000000000000000000100000000011000000001110000000111100000011");
	bitset<115> top("10000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000010000000");
	bitset<115> bottom("100000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000100");
	bitset<115> file1("1111111111");
	bitset<115> file11("1111111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

	std::bitset<115> WpawnStart("0000000000000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000000");
	std::bitset<115> BpawnStart("0000000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000000000000");

	for (int i = 0; i < 115; i++) {
		if (skipHexes.test(i)) continue;
		
		if (!top.test(i)) {
			if (!file1.test(i))
				WpawnAttacks[i].set(i - 10);
			if (!file11.test(i))
				WpawnAttacks[i].set(i + 11);
		}
		if (!bottom.test(i)) {
			if (!file1.test(i))
				BpawnAttacks[i].set(i - 11);
			if (!file11.test(i))
				BpawnAttacks[i].set(i + 10);
		}
	}
	
}

void LookupBitboard::setKnightAttacks() {
	bitset<115> skipHexes("1100000011110000000111000000001100000000010000000000000000000000000000000100000000011000000001110000000111100000011");
	
	for (int i = 0; i < 115; i++) {
		if (skipHexes.test(i)) continue;
		
		int NW_NW_SW = i + CornerW + EdgeNW;
		if (0 < NW_NW_SW && NW_NW_SW < 115 && !skipHexes.test(NW_NW_SW))
			knightAttacks[i].set(NW_NW_SW);
		int SW_SW_NW = i + CornerW + EdgeSW;
		if (0 < SW_SW_NW && SW_SW_NW < 115 && !skipHexes.test(SW_SW_NW))
			knightAttacks[i].set(SW_SW_NW);
		int NE_NE_SE = i + CornerE + EdgeNE;
		if (0 < NE_NE_SE && NE_NE_SE < 115 && !skipHexes.test(NE_NE_SE))
			knightAttacks[i].set(NE_NE_SE);
		int SE_SE_NE = i + CornerE + EdgeSE;
		if (0 < SE_SE_NE && SE_SE_NE < 115 && !skipHexes.test(SE_SE_NE))
			knightAttacks[i].set(SE_SE_NE);

		if (i != 52 && i != 63) {
			if (i != 32 && i != 42 && i != 43 && i!=53) {
				int SE_SE_S = i + CornerSE + EdgeSE;
				if (0 < SE_SE_S && SE_SE_S < 115 && !skipHexes.test(SE_SE_S))
					knightAttacks[i].set(SE_SE_S);
				if (i != 54 && i != 64 && i != 74) {
					int S_S_SE = i + CornerSE + EdgeS;
					if (0 < S_S_SE && S_S_SE < 115 && !skipHexes.test(S_S_SE))
						knightAttacks[i].set(S_S_SE);
				}
			}
			if (i != 74 && i != 85) {
				int SW_SW_S = i + CornerSW + EdgeSW;
				if (0 < SW_SW_S && SW_SW_S < 115 && !skipHexes.test(SW_SW_S))
					knightAttacks[i].set(SW_SW_S);
				if (i != 42 && i != 53 && i != 64 && i != 75) {
					int S_S_SW = i + CornerSW + EdgeS;
					if (0 < S_S_SW && S_S_SW < 115 && !skipHexes.test(S_S_SW))
						knightAttacks[i].set(S_S_SW);
				}
			}
		}
		
		if (i != 51 && i != 62) {
			if (i != 61 && i != 71 && i != 72 && i != 82) {
				int NW_NW_N = i + CornerNW + EdgeNW;
				if (0 < NW_NW_N && NW_NW_N < 115 && !skipHexes.test(NW_NW_N))
					knightAttacks[i].set(NW_NW_N);
				if (i != 40 && i != 50 && i != 60) {
					int N_N_NW = i + CornerNW + EdgeN;
					if (0 < N_N_NW && N_N_NW < 115 && !skipHexes.test(N_N_NW))
						knightAttacks[i].set(N_N_NW);
				}
			}
			if (i != 29 && i != 40) {
				int NE_NE_N = i + CornerNE + EdgeNE;
				if (0 < NE_NE_N && NE_NE_N < 115 && !skipHexes.test(NE_NE_N))
					knightAttacks[i].set(NE_NE_N);
				if (i != 39 && i != 50 && i != 61 && i != 72) {
					int N_N_NE = i + CornerNE + EdgeN;
					if (0 < N_N_NE && N_N_NE < 115 && !skipHexes.test(N_N_NE))
						knightAttacks[i].set(N_N_NE);
				}
			}
		}
	}
}

void LookupBitboard::setKingAttacks(){
}

//void LookupBitboard::setRayAttacks(){}
//bitset<92> LookupBitboard::getRookAttacks(Tile pos){}
//bitset<92> LookupBitboard::getBishopAttacks(Tile pos){}
//bitset<92> LookupBitboard::getQueenAttacks(Tile pos){}