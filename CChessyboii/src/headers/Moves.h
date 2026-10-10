#ifndef MOVES
#define MOVES
#include <stdint.h>
typedef uint32_t Move;

// 0000 0000 0000 0000 0011 1111 From Square
// 0000 0000 0000 1111 1100 0000 To Square
// 0000 0000 0001 0000 0000 0000 Color
// 0000 0000 1110 0000 0000 0000 Piece
// 0000 0111 0000 0000 0000 0000 Promoted Piece
// 0000 1000 0000 0000 0000 0000 Capture
// 0001 0000 0000 0000 0000 0000 En Passant
// 0010 0000 0000 0000 0000 0000 Double Push
// 0100 0000 0000 0000 0000 0000 Castle

inline Move encode_move(
    int from, int to, int color, int piece,
    int promoted_piece, int capture, int en_passant,
    int double_push, int castle
) {
    return (Move)(
        from
        | (to << 6)
        | (color << 12)
        | (piece << 13)
        | (promoted_piece << 16)
        | (capture << 19)
        | (en_passant << 20)
        | (double_push << 21)
        | (castle << 22)
        );
}

inline unsigned int move_get_from(Move move) {
    return move & 63;
}

inline unsigned int move_get_to(Move move) {
    return (move >> 6) & 63;
}

inline unsigned int move_get_color(Move move) {
    return (move >> 12) & 1;
}

inline unsigned int move_get_piece(Move move) {
    return (move >> 13) & 7;
}

inline unsigned int move_get_promoted_piece(Move move) {
    return (move >> 16) & 7;
}

inline unsigned int move_get_capture(Move move) {
    return (move >> 19) & 1;
}

inline unsigned int move_get_en_passant(Move move) {
    return (move >> 20) & 1;
}

inline unsigned int move_get_double_push(Move move) {
    return (move >> 21) & 1;
}

inline unsigned int move_get_castle(Move move) {
    return (move >> 22) & 1;
}

#endif