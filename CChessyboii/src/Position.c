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

const unsigned char piece_to_char[8] = {
    'w', 'b', 'p', 'n', 'b', 'r', 'q', 'k'
};

void parse_fen(Position* pos, const char* fen) {
    pos->color_to_move = 0;
    pos->castle_right = 0;
    pos->en_passant_sq = 0;
    pos->half_move_clock = 0;
    memset(pos->piece_bb, 0, sizeof(pos->piece_bb));

    int rank = 7;
    int file = 0;
    const char* p = fen;
    while (*p != '\0' && *p != ' ') { // piece placement
        if (*p == '/') {
            rank--;
            file = 0;
            p++;
            continue;
        }
        if (*p > '0' && *p < '9') {
            file += *p - '0';
            p++;
            continue;
        }

        int square = rank * 8 + file;
        int piece = char_to_piece[(*p & ~0x20) - 'B'];

        set_bit(&pos->piece_bb[piece], square);

        if (*p >= 'a' && *p <= 'z')
            set_bit(&pos->piece_bb[black], square);
        else
            set_bit(&pos->piece_bb[white], square);
        p++;
        file++;
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

void print_position(Position* pos) {
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d  ", rank + 1);
        for (int file = 0; file < 8; file++) {
            int empty = 1;
            for (int type = pawn; type <= king; type++) {
                int square = 8 * rank + file;
                if (get_bit(pieces(pos, white, type), square)) {
                    printf("%c ", piece_to_char[type] - 32);
                    empty = 0;
                }
                else if (get_bit(pieces(pos, black, type), square)) {
                    printf("%c ", piece_to_char[type]);
                    empty = 0;
                }
            }
            if (empty)
                printf(". ");
        }
        printf("\n");
    }
    printf("\n   a b c d e f g h\n");
    printf("\nColor     : %c", piece_to_char[pos->color_to_move]);
    printf("\nEn Passant: ");
    if (pos->en_passant_sq == no_sq)
        printf("/");
    else
        printf("%c%c", pos->en_passant_sq % 8 + 'a', pos->en_passant_sq / 8 + '1');
    printf("\nCastling  : %c %c %c %c", (pos->castle_right & white_short) ? 'K' : '-', 
                                        (pos->castle_right & white_long) ? 'Q' : '-', 
                                        (pos->castle_right & black_short) ? 'k' : '-', 
                                        (pos->castle_right & black_long) ? 'q' : '-');
    printf("\nHalfmove  : %d", pos->half_move_clock);
}

U64 occupancy(Position* pos)                   { return pos->piece_bb[white] | pos->piece_bb[black]; };
U64 occupancy_color(Position* pos, int color)  { return pos->piece_bb[color]; };
U64 pieces(Position* pos, int color, int type) { return pos->piece_bb[color] & pos->piece_bb[type]; };
U64 pieces_type(Position* pos, int type)       { return pos->piece_bb[type]; };