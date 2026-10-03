#include "headers/Bitboards.h"
/**
 * bitScanForward
 * @author Matt Taylor (2003)
 * @param bb bitboard to scan
 * @return index (0..63) of least significant one bit
 */
static int bitScanForward(U64 bb) {
	unsigned int folded;
	if (bb == 0) {
		return -1;
	}
	bb ^= bb - 1;
	folded = (int)bb ^ (bb >> 32);
	return LSB_64_TABLE[folded * 0x78291ACF >> 26];
}