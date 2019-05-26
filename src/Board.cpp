#include "Board.hpp"

#include <cassert>

Board::Board(const std::array<uint64_t, 3> board, const uint64_t tops) : board(board), tops(tops), currentPlayer(Color::White) {}

Board Board::empty() {
	const std::array<uint64_t, 3> board = { 0, 0, 0 };
	const uint64_t tops = 127;
	return Board(board, tops);
}

std::vector<Move> Board::moveList() const {
	uint64_t filteredTops = this->tops & 0x0000007f7f7f7f7f;
	std::vector<Move> moves;

	while(filteredTops != 0) {
		const size_t sq = __builtin_ctzll(filteredTops);
		moves.push_back(sq & 7);
		filteredTops &= filteredTops - 1;
	}

	return moves;
}

void Board::doMove(const Move column) {
	assert(column >= 0);
	assert(column < 8);

	const uint64_t top = this->tops & columns[column];

	const Color side = this->currentPlayer;

	this->board[playerToIndex(side)] |= top;
	this->board[2] |= top;

	this->tops ^= top | (top << 8);
	this->switchPlayer();
}
