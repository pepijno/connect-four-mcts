#pragma once

#include <array>
#include <iostream>

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

		uint64_t getBoard(const Color color) const;
		Color getPlayer() const { return this->currentPlayer; };

		void doMove(const uint8_t column);
};

inline uint64_t Board::getBoard(const Color color) const {
	switch (color) {
		case Color::White:
			return this->board[0];
		case Color::Black:
			return this->board[1];
		default:
			return this->board[2];
	}
}

inline void Board::switchPlayer() {
	this->currentPlayer = otherPlayer(this->currentPlayer);
}

inline std::ostream& operator<<(std::ostream &strm, const Board &board) {
	for (size_t j = 5; j >= 0 && j < 6; --j) {
		for (size_t i = 0; i < 7; ++i) {
			const size_t pos = i + j * 8;
			if ((board.getBoard(Color::White) >> pos) & 1) {
				strm << "X";
			} else if ((board.getBoard(Color::Black) >> pos) & 1) {
				strm << "O";
			} else {
				strm << ".";
			}
		}
		strm << "\n";
	}
	strm << "\n";
	strm << "Player: " << board.getPlayer() << "\n";
	return strm;
}
