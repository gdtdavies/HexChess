#pragma once
#include <vector>
#include <bitset>

using namespace std;

class BitBoard {
public:
	bitset<115> Wpawns   = bitset<115>(0), Bpawns   = bitset<115>(0);
	bitset<115> Wknights = bitset<115>(0), Bknights = bitset<115>(0);
	bitset<115> Wbishops = bitset<115>(0), Bbishops = bitset<115>(0);
	bitset<115> Wrooks   = bitset<115>(0), Brooks   = bitset<115>(0);
	bitset<115> Wqueens  = bitset<115>(0), Bqueens  = bitset<115>(0);
	bitset<115> Wking    = bitset<115>(0), Bking    = bitset<115>(0);

	bitset<115> Wpieces = Wpawns | Wknights | Wbishops | Wrooks | Wqueens | Wking;
	bitset<115> Bpieces = Bpawns | Bknights | Bbishops | Brooks | Bqueens | Bking;

	bitset<115> Occupied = Wpieces | Bpieces;

	const bitset<115> SkipHexes  = bitset<115>("1100000011110000000111000000001100000000010000000000000000000000000000000100000000011000000001110000000111100000011");
	const bitset<115> DarkHexes  = bitset<115>("0000100100000100100000100100100000100100100100100100100100100100100100100000100100100100100100000100100000000100100");
	const bitset<115> MedHexes   = bitset<115>("0001001000001001001000001001000001001001001001001001001001001001001001001001001001000001001000001001001000001001000");
	const bitset<115> LightHexes = bitset<115>("0010010000010010010000010010010010010010000010010010010010010010010010010010010010000010010010010010010000010010000");

	const bitset<115> Afile = bitset<115>("0011111100");
	const bitset<115> Bfile = bitset<115>("00111111100000000000");
	const bitset<115> Cfile = bitset<115>("0111111110000000000000000000000");
	const bitset<115> Dfile = bitset<115>("01111111110000000000000000000000000000000");
	const bitset<115> Efile = bitset<115>("1111111111000000000000000000000000000000000000000000");
	const bitset<115> Ffile = bitset<115>("111111111110000000000000000000000000000000000000000000000000000");
	const bitset<115> Gfile = bitset<115>("1111111111000000000000000000000000000000000000000000000000000000000000000");
	const bitset<115> Hfile = bitset<115>("011111111100000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<115> Ifile = bitset<115>("0111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<115> Jfile = bitset<115>("001111111000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	const bitset<115> Kfile = bitset<115>("0011111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

	const bitset<115> Files[11] = { Afile, Bfile, Cfile, Dfile, Efile, Ffile, Gfile, Hfile, Ifile, Jfile, Kfile };

	const bitset<115> Rank01 = bitset<115>("0000000000000000000000000000000000000000000000000000000000000010000000001000000000100000000010000000001000000000100");
	const bitset<115> Rank02 = bitset<115>("0000000000000000000000000000000000000000000000000001000000000100000000010000000001000000000100000000010000000001000");
	const bitset<115> Rank03 = bitset<115>("0000000000000000000000000000000000000000100000000010000000001000000000100000000010000000001000000000100000000010000");
	const bitset<115> Rank04 = bitset<115>("0000000000000000000000000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000");
	const bitset<115> Rank05 = bitset<115>("0000000000000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000");
	const bitset<115> Rank06 = bitset<115>("0000000000000000010000000001000000000100000000010000000001000000000100000000010000000001000000000100000000010000000");
	const bitset<115> Rank07 = bitset<115>("0000000100000000100000000010000000001000000000100000000010000000001000000000100000000010000000001000000000000000000");
	const bitset<115> Rank08 = bitset<115>("0000001000000001000000000100000000010000000001000000000100000000010000000001000000000100000000000000000000000000000");
	const bitset<115> Rank09 = bitset<115>("0000010000000010000000001000000000100000000010000000001000000000100000000010000000000000000000000000000000000000000");
	const bitset<115> Rank10 = bitset<115>("0000100000000100000000010000000001000000000100000000010000000001000000000000000000000000000000000000000000000000000");
	const bitset<115> Rank11 = bitset<115>("0001000000001000000000100000000010000000001000000000100000000000000000000000000000000000000000000000000000000000000");

	const bitset<115> Ranks[11] = { Rank01, Rank02, Rank03, Rank04, Rank05, Rank06, Rank07, Rank08, Rank09, Rank10, Rank11 };

	const bitset<115> RevRank01 = bitset<115>("0000000100000000001000000000010000000000100000000001000000000010000000000000000000000000000000000000000000000000000");
	const bitset<115> RevRank02 = bitset<115>("0000001000000000010000000000100000000001000000000010000000000100000000001000000000000000000000000000000000000000000");
	const bitset<115> RevRank03 = bitset<115>("0000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000000000000000000000000000");
	const bitset<115> RevRank04 = bitset<115>("0000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000000000000000");
	const bitset<115> RevRank05 = bitset<115>("0001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000000");
	const bitset<115> RevRank06 = bitset<115>("0010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100");
	const bitset<115> RevRank07 = bitset<115>("0000000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000");
	const bitset<115> RevRank08 = bitset<115>("0000000000000000000000100000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000");
	const bitset<115> RevRank09 = bitset<115>("0000000000000000000000000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000");
	const bitset<115> RevRank10 = bitset<115>("0000000000000000000000000000000000000000001000000000010000000000100000000001000000000010000000000100000000001000000");
	const bitset<115> RevRank11 = bitset<115>("0000000000000000000000000000000000000000000000000000100000000001000000000010000000000100000000001000000000010000000");

	const bitset<115> Bottom = bitset<115>("0000000100000000001000000000010000000000100000000001000000000010000000001000000000100000000010000000001000000000100");
	const bitset<115> Top    = bitset<115>("0010000000001000000000100000000010000000001000000000100000000001000000000010000000000100000000001000000000010000000");
};

