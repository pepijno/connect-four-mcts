#include "Node.hpp"

#include <algorithm>
#include <random>

Node::Node(Node* parent, const Board& board) : board(board), score(0.0), visits(0), winScore(0) {
	this->parent = parent;

	this->movesLeft = this->board.moveList();
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(this->movesLeft), std::end(this->movesLeft), rng);
}
