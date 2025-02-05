#pragma once

const enum Colour : int { white, black, red, NA };
const enum Type : int { pawn, knight, bishop, rook, queen, king, empty };
const enum Tile : int {
o1, o2,      a1, a2, a3, a4, a5, a6,      o3, o4,
o5,o6,     b1, b2, b3, b4, b5, b6, b7,     o7,o8,
o9,      c1, c2, c3, c4, c5, c6, c7, c8,     o10,
o11,   d1, d2, d3, d4, d5, d6, d7, d8, d9,   o12,
     e1, e2, e3, e4, e5, e6, e7, e8, e9, e10,
   f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
     g2, g3, g4, g5, g6, g7, g8, g9, g10, g11,
o13,   h3, h4, h5, h6, h7, h8, h9, h10, h11, o14,
o15,     i4, i5, i6, i7, i8, i9, i10, i11,   o16,
o17,o18,  j5, j6, j7, j8, j9, j10, j11,  o19,o20,
o21,o22,    k6, k7, k8, k9, k10, k11,    o23,o24,
                       none
};
const enum Direction : int {
   EdgeNW = -10, EdgeN = 1, EdgeNE = 11, EdgeSE = 10, EdgeS = -1, EdgeSW = -11,
   CornerW = -21, CornerNW = -9, CornerNE = 12, CornerE = 21, CornerSE = 9, CornerSW = -12
};
const enum Promotion : int { toNone, toKnight, toBishop, toRook, toQueen };

const int hex_count = 115;