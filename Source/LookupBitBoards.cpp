#include "../Headers/LookupBitboards.h"

//-----------------------------------------------------------------------------
//-private methods-------------------------------------------------------------
//-----------------------------------------------------------------------------

int LookupBitboard::bitScan(bitset<115> mask, bool isNegative) {
	//unsigned long index;
	if (!isNegative) {
		for (int hex = 0; hex < 115; hex++) {
			if (mask.test(hex)) return hex;
		}
	}
	else {
		for (int hex = 114; hex > 0; hex--) {
			if (mask.test(hex)) return hex;
		}
	}
}
bitset<115> LookupBitboard::getRayAttacks(bitset<115> occupied, Direction dir, Tile hex) {
	int dirIndex = dir == EdgeNW ? 0 : dir == EdgeN ? 1 : dir == EdgeNE ? 2 : dir == EdgeSE ? 3 : dir == EdgeS ? 4 : dir == EdgeSW ? 5 
		: dir == CornerW ? 6 : dir == CornerNW ? 7 : dir == CornerNE ? 8 : dir == CornerE ? 9 : dir == CornerSE ? 10 : dir == CornerSW ? 11 : 12;
	bitset<115> attacks = rayAttacks[hex][dirIndex];
	bitset<115> blockers = attacks & occupied;
	if (blockers.any()) {
		Tile blocker = (Tile)bitScan(blockers, isNegative(dir));
		attacks ^= rayAttacks[blocker][dirIndex];
	}
	return attacks;
}

//-----------------------------------------------------------------------------
//-public methods--------------------------------------------------------------
//-----------------------------------------------------------------------------

void LookupBitboard::setPawnMoves(BitBoard& bb) {
	std::bitset<115> WpawnStart("0000000000000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000000");
	std::bitset<115> BpawnStart("0000000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000000000000");

	for (int i = 0; i < 115; i++) {
		if (bb.SkipHexes.test(i)) continue;
		if (!bb.Top.test(i)) {
			WpawnMoves[i].set(i + 1);
			if (WpawnStart.test(i)) 
				WpawnMoves[i].set(i + 2);
		}
		if (!bb.Bottom.test(i)) {
			BpawnMoves[i].set(i - 1);
			if (BpawnStart.test(i))
				BpawnMoves[i].set(i - 2);
		}
	}
	
}
void LookupBitboard::setPawnAttacks(BitBoard& bb) {
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

void LookupBitboard::setKnightAttacks(BitBoard& bb) {
	
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

void LookupBitboard::setKingAttacks(BitBoard& bb){
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

void LookupBitboard::setRayAttacks(BitBoard& bb){
	for (int origin = 0; origin < 115; origin++) {
		if (bb.SkipHexes.test(origin)) 
			continue;
		
		int oFile = bb.Afile.test(origin) ? 0 : bb.Bfile.test(origin) ? 1 : bb.Cfile.test(origin) ? 2: bb.Dfile.test(origin) ? 3
			: bb.Efile.test(origin) ? 4: bb.Ffile.test(origin) ? 5 : bb.Gfile.test(origin) ? 6: bb.Hfile.test(origin) ? 7
			: bb.Ifile.test(origin) ? 8: bb.Jfile.test(origin) ? 9 : bb.Kfile.test(origin) ? 10 : 11;	
		int oRank = bb.Rank01.test(origin) ? 0 : bb.Rank02.test(origin) ? 1 : bb.Rank03.test(origin) ? 2: bb.Rank04.test(origin) ? 3
			: bb.Rank05.test(origin) ? 4: bb.Rank06.test(origin) ? 5 : bb.Rank07.test(origin) ? 6: bb.Rank08.test(origin) ? 7
			: bb.Rank09.test(origin) ? 8: bb.Rank10.test(origin) ? 9 : bb.Rank11.test(origin) ? 10 : 11;
		int oRevRank = bb.RevRank01.test(origin) ? 0 : bb.RevRank02.test(origin) ? 1 : bb.RevRank03.test(origin) ? 2: bb.RevRank04.test(origin) ? 3
			: bb.RevRank05.test(origin) ? 4: bb.RevRank06.test(origin) ? 5 : bb.RevRank07.test(origin) ? 6: bb.RevRank08.test(origin) ? 7
			: bb.RevRank09.test(origin) ? 8: bb.RevRank10.test(origin) ? 9 : bb.RevRank11.test(origin) ? 10 : 11;
		
		for (int target = 0; target < 115; target++) {
			if (bb.SkipHexes.test(target) || origin == target) 
				continue;

			int tFile = bb.Afile.test(target) ? 0 : bb.Bfile.test(target) ? 1 : bb.Cfile.test(target) ? 2 : bb.Dfile.test(target) ? 3 
				: bb.Efile.test(target) ? 4 : bb.Ffile.test(target) ? 5 : bb.Gfile.test(target) ? 6 : bb.Hfile.test(target) ? 7 
				: bb.Ifile.test(target) ? 8 : bb.Jfile.test(target) ? 9 : bb.Kfile.test(target) ? 10 : 11;
			int tRank = bb.Rank01.test(target) ? 0 : bb.Rank02.test(target) ? 1 : bb.Rank03.test(target) ? 2 : bb.Rank04.test(target) ? 3 
				: bb.Rank05.test(target) ? 4 : bb.Rank06.test(target) ? 5 : bb.Rank07.test(target) ? 6 : bb.Rank08.test(target) ? 7 
				: bb.Rank09.test(target) ? 8 : bb.Rank10.test(target) ? 9 : bb.Rank11.test(target) ? 10 : 11;
			int tRevRank = bb.RevRank01.test(target) ? 0 : bb.RevRank02.test(target) ? 1 : bb.RevRank03.test(target) ? 2 : bb.RevRank04.test(target) ? 3 
				: bb.RevRank05.test(target) ? 4 : bb.RevRank06.test(target) ? 5 : bb.RevRank07.test(target) ? 6 : bb.RevRank08.test(target) ? 7 
				: bb.RevRank09.test(target) ? 8 : bb.RevRank10.test(target) ? 9 : bb.RevRank11.test(target) ? 10 : 11;
						
			if (origin > target) {
				if (tRank == oRank)							//EdgeNW
					rayAttacks[origin][0].set(target);
				else if (tFile == oFile)					//EdgeS
					rayAttacks[origin][4].set(target);
				else if (tRevRank == oRevRank)			//EdgeSW
					rayAttacks[origin][5].set(target);

				else if ((origin - target) % CornerW == 0)									//CornerW
					rayAttacks[origin][6].set(target);
				else if ((origin - target) % CornerNW == 0 && tRank > oRank)			//CornerNW
					rayAttacks[origin][7].set(target);
				else if ((origin - target) % CornerSW == 0 && tRevRank < oRevRank)	//CornerSW
					rayAttacks[origin][11].set(target);
			}
			else {
				if (tFile == oFile)							//EdgeN
					rayAttacks[origin][1].set(target);
				else if (tRevRank == oRevRank)			//EdgeNE
					rayAttacks[origin][2].set(target);
				else if (tRank == oRank)					//EdgeSE
					rayAttacks[origin][3].set(target);

				else if ((target - origin) % CornerNE == 0 && tRevRank > oRevRank)	//CornerNE
					rayAttacks[origin][8].set(target);
				else if ((target - origin) % CornerE == 0)									//CornerE
					rayAttacks[origin][9].set(target);
				else if ((target - origin) % CornerSE == 0 && tRank < oRank)			//CornerSE	
					rayAttacks[origin][10].set(target);
			}
		}
	}
}