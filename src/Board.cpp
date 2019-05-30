#include "Board.hpp"

#include <cassert>
#include <random>

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

	if (this->lastMoveWasWinningMove() || __builtin_popcountll(this->board[2])) {
		this->over = true;
	}
}

bool Board::lastMoveWasWinningMove() const {
	uint64_t b = this->board[playerToIndex(otherPlayer(this->currentPlayer))];
	uint64_t t = b & (b >> 8);
	if (t & (t >> 16)) {
		return true;
	}
	t = b & (b >> 1);
	if (t & (t >> 2)) {
		return true;
	}
	t = b & (b >> 7);
	if (t & (t >> 14)) {
		return true;
	}
	t = b & (b >> 9);
	if (t & (t >> 18)) {
		return true;
	}
	return false;
}

void Board::randomGame() {
	std::random_device rd;
	std::mt19937 rng(rd());
	while(!this->over) {
		const std::vector<Move> moveList = this->moveList();

		std::uniform_int_distribution<int> uniform(0, moveList.size() - 1);

		const int index = uniform(rng);

		const Move move = moveList.at(index);
		
		this->doMove(move);
	}
}
