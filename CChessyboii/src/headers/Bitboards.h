#ifndef BITBOARDS
#define BITBOARDS

#define U64 unsigned long long int

extern const U64 A_FILE;
extern const U64 H_FILE;
extern const U64 FIRST_RANK;
extern const U64 LAST_RANK;
extern const U64 A1H8_DIAGONAL;
extern const U64 H1A8_DIAGONAL;
extern const U64 LIGHT_SQUARES;
extern const U64 DARK_SQUARES;

extern const int LSB_64_TABLE[64];

static inline void set_bit(U64* bitboard, int square) {
    *bitboard |= 1ULL << square;
}

static inline int get_bit(U64 bitboard, int square) {
    return (bitboard >> square) & 1ULL;
}

static inline void pop_bit(U64* bitboard, int square) {
    *bitboard &= ~(1ULL << square);
}

int bit_scan_forward(U64 bb);
void print_bitboard(U64 bb);

#endif