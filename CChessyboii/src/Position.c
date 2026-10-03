#include "headers/Position.h"

U64 occupancy(void)             { return pieceBB[white] | pieceBB[black]; };
U64 occupancy_color(int color)  { return pieceBB[color]; };
U64 pieces(int color, int type) { return pieceBB[color] & pieceBB[type]; };
U64 pieces_type(int type)       { return pieceBB[type]; };