#pragma once

#define U64 unsigned long long int

const U64 A_FILE        = 0x0101010101010101;
const U64 H_FILE        = 0x8080808080808080;
const U64 FIRST_RANK    = 0x00000000000000FF;
const U64 LAST_RANK     = 0xFF00000000000000;
const U64 A1H8_DIAGONAL = 0x8040201008040201;
const U64 H1A8_DIAGONAL = 0x0102040810204080;
const U64 LIGHT_SQUARES = 0x55AA55AA55AA55AA;
const U64 DARK_SQUARES  = 0xAA55AA55AA55AA55;

#define setBit(bitboard, square) (bitboard |= (1ULL >> square))
#define getBit(bitboard, square) (bitboard & (1ULL >> square))
#define popBit(bitboard, square) (bitboard &= ~(1ULL >> square))

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

static int bitScanForward(U64 bb);