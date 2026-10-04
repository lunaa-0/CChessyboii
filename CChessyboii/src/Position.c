#include "headers/Position.h"
#include <stdio.h>

const unsigned char char_to_piece[17] = {
    [0] = bishop,
    [9] = king,
    [12] = knight,
    [14] = pawn,
    [15] = queen,
    [16] = rook
};

void parse_fen(Position* pos, const char* fen) {
    pos->color_to_move = 0;
    pos->castle_right = 0;
    pos->en_passant_sq = 0;
    pos->half_move_clock = 0;
    memset(pos->piece_bb, 0, sizeof(pos->piece_bb));

    int square = 63;
    const char* p = fen;
    while (*p != '\0' && *p != ' ') { // piece placement
        if (*p == '/') {
            p++;
            continue;
        }
        if (*p > '0' && *p < '9') {
            square -= *p - '0';
            p++;
            continue;
        }

        int piece = char_to_piece[(*p & ~0x20) - 'B'];

        set_bit(&pos->piece_bb[piece], square);

        if (*p >= 'a' && *p <= 'z')
            set_bit(&pos->piece_bb[black], square);
        else
            set_bit(&pos->piece_bb[white], square);
        p++;
        square--;
    }

    if (*p == ' ')
        p++;

    if (*p == 'w') // color to move
        pos->color_to_move = white;
    else if (*p == 'b')
        pos->color_to_move = black;
    p++;

    if (*p == ' ')
        p++;

    while (*p != ' ' && *p != '\0') { // castling rights
        switch (*p) {
        case 'K':
            pos->castle_right |= white_short;
            break;
        case 'Q':
            pos->castle_right |= white_long;
            break;
        case 'k':
            pos->castle_right |= black_short;
            break;
        case 'q':
            pos->castle_right |= black_long;
            break;
        case '-':
            break;
        }
        p++;
    }

    if (*p == ' ')
        p++;
    
    if (*p == '-') { // en Passant Square
        pos->en_passant_sq = no_sq;
        p++;
    }
    else {
        int file = p[0] - 'a';
        int rank = p[1] - '1';
        pos->en_passant_sq = rank * 8 + file;
        p += 2;
    }

    if (*p == ' ')
        p++;

    while (*p >= '0' && *p <= '9') {
        pos->half_move_clock = pos->half_move_clock * 10 + (*p - '0');
        p++;
    }
}

U64 occupancy(Position* pos)                   { return pos->piece_bb[white] | pos->piece_bb[black]; };
U64 occupancy_color(Position* pos, int color)  { return pos->piece_bb[color]; };
U64 pieces(Position* pos, int color, int type) { return pos->piece_bb[color] & pos->piece_bb[type]; };
U64 pieces_type(Position* pos, int type)       { return pos->piece_bb[type]; };