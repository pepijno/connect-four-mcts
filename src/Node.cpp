#include "Node.hpp"

#include <algorithm>
#include <random>

Node::Node(const Board& board) : board(board), score(0.0), visits(0), winScore(0) {
	std::vector<Move> moves = this->board.moveList();
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(moves), std::end(moves), rng);
	std::queue<Move> movesLeft;
	for (const Move move : moves) {
		movesLeft.push(move);
	}
	this-> movesLeft = movesLeft;
}
