#pragma once

const enum Colour : int { white, black, NA };
const enum Type : int { pawn, knight, bishop, rook, queen, king, empty };
const enum Hexagon : int {
				 a1, a2, a3, a4, a5, a6,
			  b1, b2, b3, b4, b5, b6, b7,
			c1, c2, c3, c4, c5, c6, c7, c8,
		 d1, d2, d3, d4, d5, d6, d7, d8, d9,
	  e1, e2, e3, e4, e5, e6, e7, e8, e9, e10,
	f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
	  g2, g3, g4, g5, g6, g7, g8, g9, g10, g11,
		 h3, h4, h5, h6, h7, h8, h9, h10, h11,
			i4, i5, i6, i7, i8, i9, i10, i11,
			  j5, j6, j7, j8, j9, j10, j11,
				 k6, k7, k8, k9, k10, k11,
								none
};

