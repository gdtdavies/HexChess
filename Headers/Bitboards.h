#pragma once
#include <vector>
#include <bitset>
#include "Enums.h"

using namespace std;

class BitBoard {
public:
	bitset<hex_count> Wpawns  , Bpawns  ;
	bitset<hex_count> Wknights, Bknights;
	bitset<hex_count> Wbishops, Bbishops;
	bitset<hex_count> Wrooks  , Brooks  ;
	bitset<hex_count> Wqueens , Bqueens ;
	bitset<hex_count> Wking   , Bking   ;

	bitset<hex_count> Wpieces;
	bitset<hex_count> Bpieces;

	bitset<hex_count> Occupied;

	//-Masks---
	const bitset<hex_count> SkipHexes  = bitset<hex_count>("1100000011110000000111000000001100000000010000000000000000000000000000000100000000011000000001110000000111100000011");
	const bitset<hex_count> DarkHexes  = bitset<hex_count>("0000100100000100100000100100100000100100100100100100100100100100100100100000100100100100100100000100100000000100100");
	const bitset<hex_count> MedHexes   = bitset<hex_count>("0001001000001001001000001001000001001001001001001001001001001001001001001001001001000001001000001001001000001001000");
	const bitset<hex_count> LightHexes = bitset<hex_count>("0010010000010010010000010010010010010010000010010010010010010010010010010010010010000010010010010010010000010010000");

	const bitset<hex_count> Afile = bitset<hex_count>("0011111100");
	const bitset<hex_count> Bfile = bitset<hex_count>("001111111000000000000");
	const bitset<hex_count> Cfile = bitset<hex_count>("0111111110000000000000000000000");
	const bitset<hex_count> Dfile = bitset<hex_count>("011111111100000000000000000000000000000000");
	const bitset<hex_count> Efile = bitset<hex_count>("1111111111000000000000000000000000000000000000000000");
	const bitset<hex_count> Ffile = bitset<hex_count>("111111111110000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Gfile = bitset<hex_count>("1111111111000000000000000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Hfile = bitset<hex_count>("011111111100000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Ifile = bitset<hex_count>("0111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Jfile = bitset<hex_count>("001111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Kfile = bitset<hex_count>("0011111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

	const bitset<hex_count> Files[11] = { Afile, Bfile, Cfile, Dfile, Efile, Ffile, Gfile, Hfile, Ifile, Jfile, Kfile };

	const bitset<hex_count> Rank01 = bitset<hex_count>("0000000000000000000000000000000000000000000000000000000000000010000000001000000000100000000010000000001000000000100");
	const bitset<hex_count> Rank02 = bitset<hex_count>("0000000000000000000000000000000000000000000000000001000000000100000000010000000001000000000100000000010000000001000");
	const bitset<hex_count> Rank03 = bitset<hex_count>("0000000000000000000000000000000000000000100000000010000000001000000000100000000010000000001000000000100000000010000");
	const bitset<hex_count> Rank04 = bitset<hex_count>("0000000000000000000000000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000");
	const bitset<hex_count> Rank05 = bitset<hex_count>("0000000000000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000");
	const bitset<hex_count> Rank06 = bitset<hex_count>("0000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000");
	const bitset<hex_count> Rank07 = bitset<hex_count>("0000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000000000000");
	const bitset<hex_count> Rank08 = bitset<hex_count>("0000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000000000000000000000000");
	const bitset<hex_count> Rank09 = bitset<hex_count>("0000100000000010000000001000000000100000000010000000001000000000100000000010000000000000000000000000000000000000000");
	const bitset<hex_count> Rank10 = bitset<hex_count>("0001000000000100000000010000000001000000000100000000010000000001000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> Rank11 = bitset<hex_count>("0010000000001000000000100000000010000000001000000000100000000000000000000000000000000000000000000000000000000000000");

	const bitset<hex_count> Ranks[11] = { Rank01, Rank02, Rank03, Rank04, Rank05, Rank06, Rank07, Rank08, Rank09, Rank10, Rank11 };

	const bitset<hex_count> RevRank01 = bitset<hex_count>("0000000100000000001000000000010000000000100000000001000000000010000000000000000000000000000000000000000000000000000");
	const bitset<hex_count> RevRank02 = bitset<hex_count>("0000001000000000010000000000100000000001000000000010000000000100000000001000000000000000000000000000000000000000000");
	const bitset<hex_count> RevRank03 = bitset<hex_count>("0000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000000000000000000000000000");
	const bitset<hex_count> RevRank04 = bitset<hex_count>("0000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000000000000000");
	const bitset<hex_count> RevRank05 = bitset<hex_count>("0001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000000");
	const bitset<hex_count> RevRank06 = bitset<hex_count>("0010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100");
	const bitset<hex_count> RevRank07 = bitset<hex_count>("0000000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000");
	const bitset<hex_count> RevRank08 = bitset<hex_count>("0000000000000000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000");
	const bitset<hex_count> RevRank09 = bitset<hex_count>("0000000000000000000000000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000");
	const bitset<hex_count> RevRank10 = bitset<hex_count>("0000000000000000000000000000000000000000001000000000010000000000100000000001000000000010000000000100000000001000000");
	const bitset<hex_count> RevRank11 = bitset<hex_count>("0000000000000000000000000000000000000000000000000000100000000001000000000010000000000100000000001000000000010000000");

	const bitset<hex_count> Bottom = Rank01 | RevRank01;
	const bitset<hex_count> Top    = Rank11 | RevRank11;

	const bitset<hex_count> WpawnStarts = bitset<hex_count>("0000000000000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000000");
	const bitset<hex_count> BpawnStarts = bitset<hex_count>("0000000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000000000000");
};

