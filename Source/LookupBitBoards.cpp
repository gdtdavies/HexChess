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
	std::bitset<115> WpawnStart("0000000000000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000000");
	std::bitset<115> BpawnStart("0000000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000000000000");

	for (int i = 0; i < 115; i++) {
		if (bb.SkipHexes.test(i)) continue;
		if (!bb.Top.test(i)) {
			WpawnAttacks[i].set(i + 1);
			if (WpawnStart.test(i)) 
				WpawnMoves[i].set(i + 2);
		}
		if (!bb.Bottom.test(i)) {
			BpawnAttacks[i].set(i - 1);
			if (BpawnStart.test(i))
				BpawnMoves[i].set(i - 2);
		}
	}
	
}
void LookupBitboard::setPawnAttacks() {
	for (int i = 0; i < 115; i++) {
		if (bb.SkipHexes.test(i)) continue;
		
		if (!bb.Top.test(i)) {
			if (!bb.Afile.test(i))
				WpawnAttacks[i].set(i - 10);
			if (!bb.Kfile.test(i))
				WpawnAttacks[i].set(i + 11);
		}
		if (!bb.Bottom.test(i)) {
			if (!bb.Afile.test(i))
				BpawnAttacks[i].set(i - 11);
			if (!bb.Kfile.test(i))
				BpawnAttacks[i].set(i + 10);
		}
	}
	
}

void LookupBitboard::setKnightAttacks() {
	
	for (int i = 0; i < 115; i++) {
		if (bb.SkipHexes.test(i)) continue;
		
		int NW_NW_SW = i + CornerW + EdgeNW;
		if (0 < NW_NW_SW && NW_NW_SW < 115 && !bb.SkipHexes.test(NW_NW_SW))
			knightAttacks[i].set(NW_NW_SW);
		int SW_SW_NW = i + CornerW + EdgeSW;
		if (0 < SW_SW_NW && SW_SW_NW < 115 && !bb.SkipHexes.test(SW_SW_NW))
			knightAttacks[i].set(SW_SW_NW);
		int NE_NE_SE = i + CornerE + EdgeNE;
		if (0 < NE_NE_SE && NE_NE_SE < 115 && !bb.SkipHexes.test(NE_NE_SE))
			knightAttacks[i].set(NE_NE_SE);
		int SE_SE_NE = i + CornerE + EdgeSE;
		if (0 < SE_SE_NE && SE_SE_NE < 115 && !bb.SkipHexes.test(SE_SE_NE))
			knightAttacks[i].set(SE_SE_NE);

		if (i != 52 && i != 63) {
			if (i != 32 && i != 42 && i != 43 && i!=53) {
				int SE_SE_S = i + CornerSE + EdgeSE;
				if (0 < SE_SE_S && SE_SE_S < 115 && !bb.SkipHexes.test(SE_SE_S))
					knightAttacks[i].set(SE_SE_S);
				if (i != 54 && i != 64 && i != 74) {
					int S_S_SE = i + CornerSE + EdgeS;
					if (0 < S_S_SE && S_S_SE < 115 && !bb.SkipHexes.test(S_S_SE))
						knightAttacks[i].set(S_S_SE);
				}
			}
			if (i != 74 && i != 85) {
				int SW_SW_S = i + CornerSW + EdgeSW;
				if (0 < SW_SW_S && SW_SW_S < 115 && !bb.SkipHexes.test(SW_SW_S))
					knightAttacks[i].set(SW_SW_S);
				if (i != 42 && i != 53 && i != 64 && i != 75) {
					int S_S_SW = i + CornerSW + EdgeS;
					if (0 < S_S_SW && S_S_SW < 115 && !bb.SkipHexes.test(S_S_SW))
						knightAttacks[i].set(S_S_SW);
				}
			}
		}
		
		if (i != 51 && i != 62) {
			if (i != 61 && i != 71 && i != 72 && i != 82) {
				int NW_NW_N = i + CornerNW + EdgeNW;
				if (0 < NW_NW_N && NW_NW_N < 115 && !bb.SkipHexes.test(NW_NW_N))
					knightAttacks[i].set(NW_NW_N);
				if (i != 40 && i != 50 && i != 60) {
					int N_N_NW = i + CornerNW + EdgeN;
					if (0 < N_N_NW && N_N_NW < 115 && !bb.SkipHexes.test(N_N_NW))
						knightAttacks[i].set(N_N_NW);
				}
			}
			if (i != 29 && i != 40) {
				int NE_NE_N = i + CornerNE + EdgeNE;
				if (0 < NE_NE_N && NE_NE_N < 115 && !bb.SkipHexes.test(NE_NE_N))
					knightAttacks[i].set(NE_NE_N);
				if (i != 39 && i != 50 && i != 61 && i != 72) {
					int N_N_NE = i + CornerNE + EdgeN;
					if (0 < N_N_NE && N_N_NE < 115 && !bb.SkipHexes.test(N_N_NE))
						knightAttacks[i].set(N_N_NE);
				}
			}
		}
	}
}

void LookupBitboard::setKingAttacks(){
	for (int i = 0; i < 115; i++) {
		if (bb.SkipHexes.test(i)) continue;
		
		if (!(bb.Afile | bb.RevRank11).test(i)) 
			kingAttacks[i].set(i + EdgeNW);
		if (!bb.Top.test(i))
			kingAttacks[i].set(i + EdgeN);
		if (!(bb.Kfile | bb.Rank11).test(i)) 
			kingAttacks[i].set(i + EdgeNE);
		if (!(bb.Kfile | bb.RevRank01).test(i)) 
			kingAttacks[i].set(i + EdgeSE);
		if (!bb.Bottom.test(i))
			kingAttacks[i].set(i + EdgeS);
		if (!(bb.Afile | bb.Rank01).test(i)) 
			kingAttacks[i].set(i + EdgeSW);

		if (!(bb.Afile | bb.Bfile | bb.Rank01 | bb.RevRank11).test(i))
			kingAttacks[i].set(i + CornerW);
		if (!(bb.Afile | bb.Top | bb.RevRank10).test(i))
			kingAttacks[i].set(i + CornerNW);
		if (!(bb.Kfile | bb.Top | bb.Rank10).test(i))
			kingAttacks[i].set(i + CornerNE);
		if (!(bb.Kfile | bb.Jfile | bb.Rank11 | bb.RevRank01).test(i))
			kingAttacks[i].set(i + CornerE);
		if (!(bb.Kfile | bb.Bottom | bb.RevRank02).test(i))
			kingAttacks[i].set(i + CornerSE);
		if (!(bb.Afile | bb.Bottom | bb.Rank02).test(i))
			kingAttacks[i].set(i + CornerSW);
	}
}

//void LookupBitboard::setRayAttacks(){}
//bitset<92> LookupBitboard::getRookAttacks(Tile pos){}
//bitset<92> LookupBitboard::getBishopAttacks(Tile pos){}
//bitset<92> LookupBitboard::getQueenAttacks(Tile pos){}