#pragma once

#include <array>

#include "Util.hpp"

class Board
{
	private:
		std::array<uint64_t, 3> board;
		uint64_t tops;
		Color currentPlayer;

		void switchPlayer();
	public:
		Board(const std::array<uint64_t, 3> board, const uint64_t tops);
		static Board empty();

		void doMove(const uint8_t column, const Color side);
};

inline void Board::switchPlayer() {
	this->currentPlayer = otherPlayer(this->currentPlayer);
}
