#ifndef POSITION
#define POSITION

#include "Bitboards.h"

/* bin   dec
   0001    1  white king can castle to the king side
   0010    2  white king can castle to the queen side
   0100    4  black king can castle to the king side
   1000    8  black king can castle to the queen side

   examples:
   1111       both sides can castle both directions
   1001       black king => queen side
			  white king => king side
 */
enum enumCastleRight {
	white_short = 1, white_long = 2, black_short = 4, black_long = 8
};

enum enumSquare {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8, no_sq
};

enum enumPiece {
	white, black, pawn, knight, bishop, rook, queen, king
};

// convert from ASCII char to encoded piece constant
extern const unsigned char char_to_piece[17];
// convert from encoded piece constant to ASCII CHAR
extern const unsigned char piece_to_char[8];

typedef struct {
	U64 piece_bb[8];

	int color_to_move;
	int en_passant_sq;
	int castle_right;
	int half_move_clock;
} Position;

void parse_fen(Position* pos, const char* fen);
void print_position(Position* pos);

U64 occupancy(Position* pos);             // all pieces
U64 occupancy_color(Position* pos, int color);  // all pieces of a color
U64 pieces(Position* pos, int color, int type); // pieces of a color/type
U64 pieces_type(Position* pos, int type);       // all pieces of a type

#endif