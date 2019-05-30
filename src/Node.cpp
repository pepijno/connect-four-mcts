#include "Node.hpp"

#include <algorithm>
#include <random>
#include <cfloat>

const double c = 2.0;

Node::Node(Node* parent, const Board& board) : board(board), score(0.0), visits(0), winScore(0) {
	this->parent = parent;

	this->moves = this->board.moveList();
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(this->moves), std::end(this->moves), rng);
}

bool Node::isTerminal() const {
	return this->board.isOver();
}

bool Node::isExpanded() const {
	return this->children.size() != 0 && this->moves.size() == this->children.size();
}

Node Node::expand() {
	if (this->isExpanded()) {
		return *this;
	}

	return this->addChild(this->moves[this->children.size()]);
}

Node Node::addChild(const Move move) {
	Board board = Board(this->board);
	board.doMove(move);

	Node node = Node(this, board);

	this->children.push_back(node);

	return node;
}

Node Node::bestChild() const {
	const int parentVisits = this->visits;
	return *std::max_element( this->children.begin(), this->children.end(),
			[&parentVisits](const Node& a, const Node& b) {
				return a.uct(parentVisits) > b.uct(parentVisits);
			});
}

double Node::uct(const int parentVisits) const {
	const double utc_explore = sqrt( log( (double) parentVisits + 1 ) / ( this->visits + DBL_EPSILON ) );
	return this->score + c * utc_explore;
}
