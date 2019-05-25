#include "Board.hpp"

#include <cassert>

Board::Board(const std::array<uint64_t, 3> board, const uint64_t tops) : board(board), tops(tops), currentPlayer(Color::White) {}

Board Board::empty() {
	const std::array<uint64_t, 3> board = { 0, 0, 0 };
	const uint64_t tops = 127;
	return Board(board, tops);
}

void Board::doMove(const uint8_t column) {
	assert(column >= 0);
	assert(column < 8);

	const uint64_t top = this->tops & columns[column];

	const Color side = this->currentPlayer;

	this->board[playerToIndex(side)] |= top;
	this->board[2] |= top;

	this->tops ^= top | (top << 8);
	this->switchPlayer();
}
