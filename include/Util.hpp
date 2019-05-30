#pragma once

#include <cstdint>

const std::array<uint64_t, 8> columns = {
	0x0101010101010101,
	0x0202020202020202,
	0x0404040404040404,
	0x0808080808080808,
	0x1010101010101010,
	0x2020202020202020,
	0x4040404040404040,
	0x8080808080808080
};

enum class Color { White, Black, Both };

typedef uint8_t Move;

inline Color otherPlayer(const Color side) {
	if (side == Color::White) {
		return Color::Black;
	}
	return Color::White;
}

inline size_t playerToIndex(const Color player) {
	if (player == Color::White) {
		return 0;
	}
	return 1;
}

inline std::ostream& operator<<(std::ostream& strm, const Color& color) {
	if (color == Color::White) {
		return strm << "White";
	}
	if (color == Color::Black) {
		return strm << "Black";
	}
	return strm << "Both";
}

inline std::ostream& printBitboard(std::ostream &strm, const uint64_t bb) {
	for (size_t j = 7; j >= 0 && j < 8; --j) {
		for (size_t i = 0; i < 8; ++i) {
			const size_t pos = i + j * 8;
			if ((bb >> pos) & 1) {
				strm << "X";
			} else {
				strm << ".";
			}
		}
		strm << "\n";
	}
	strm << "\n";
	return strm;
}
