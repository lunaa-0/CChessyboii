#include "headers/Bitboards.h"
#include <stdio.h>

const U64 A_FILE = 0x0101010101010101ULL;
const U64 H_FILE = 0x8080808080808080ULL;
const U64 FIRST_RANK = 0x00000000000000FFULL;
const U64 LAST_RANK = 0xFF00000000000000ULL;
const U64 A1H8_DIAGONAL = 0x8040201008040201ULL;
const U64 H1A8_DIAGONAL = 0x0102040810204080ULL;
const U64 LIGHT_SQUARES = 0x55AA55AA55AA55AAULL;
const U64 DARK_SQUARES = 0xAA55AA55AA55AA55ULL;

const int LSB_64_TABLE[64] = {
   63, 30,  3, 32, 59, 14, 11, 33,
   60, 24, 50,  9, 55, 19, 21, 34,
   61, 29,  2, 53, 51, 23, 41, 18,
   56, 28,  1, 43, 46, 27,  0, 35,
   62, 31, 58,  4,  5, 49, 54,  6,
   15, 52, 12, 40,  7, 42, 45, 16,
   25, 57, 48, 13, 10, 39,  8, 44,
   20, 47, 38, 22, 17, 37, 36, 26
};

/**
 * bit_scan_forward
 * @author Matt Taylor (2003)
 * @param bb bitboard to scan
 * @return index (0..63) of least significant one bit
 */
int bit_scan_forward(U64 bb) {
	U64 folded;
	if (bb == 0) {
		return -1;
	}
	bb ^= bb - 1;
	folded = (int)bb ^ (bb >> 32);
	return LSB_64_TABLE[folded * 0x78291ACF >> 26];
}

void print_bitboard(U64 bb) {
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d  ", rank + 1);
        for (int file = 0; file < 8; file++) {
            printf("%d ", (int)((bb >> (8 * rank + file)) & 1ULL));
        }
        printf("\n");
    }
    printf("\n   a b c d e f g h\n");
    printf("\n   Value : %llu\n", bb);
}