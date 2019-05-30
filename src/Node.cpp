#include "Node.hpp"

#include <algorithm>
#include <random>
#include <cfloat>

const double c = 2.0;

Node::Node(Node* parent, const Board& board, const Move move) : parent(parent), board(board), move(move), score(0.0), visits(0), winScore(0) {
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

Node* Node::expand() {
	if (this->isExpanded()) {
		return this;
	}

	return this->addChild(this->moves[this->children.size()]);
}

Node* Node::addChild(const Move move) {
	Board board = Board(this->board);
	board.doMove(move);

	std::unique_ptr<Node> node(new Node(this, board, move));
	this->children.push_back(std::move(node));

	return this->children.back().get();
}

Node* Node::bestChild() const {
	const int parentVisits = this->visits;
	const auto& node = std::max_element( this->children.begin(), this->children.end(),
			[&parentVisits](const auto& a, const auto& b) {
				return a.get()->uct(parentVisits) < b.get()->uct(parentVisits);
			});
	return node->get();
}

double Node::uct(const int parentVisits) const {
	const double utc_explore = sqrt( log( (double) parentVisits + 1 ) / ( this->visits + DBL_EPSILON ) );
	return this->score + c * utc_explore;
}

void Node::print(std::ostream& os, const int level, const int indent) const {
	std::string ind = std::string(indent, ' ');

	os << ind << "Visits: " << this->visits << ", "
		<< "WinScore: " << this->winScore << ", "
		<< "Score: " << this->score << ", "
		<< "Children: " << this->children.size() << ", "
		<< "Color: " << this->board.getPlayer() << ", "
		<< "Move: " << int(this->move) << ", "
		<< "\n";

	if (level-1 > 0) {
		for (const auto& node : this->children) {
			node.get()->print(os, level - 1, indent + 2);
		}
	}
}

void Node::updateWinnerRecursive(const Color winner) {
	++this->visits;

	if (winner == this->board.getPlayer()) {
		++this->winScore;
	} else if (winner != Color::Both) {
		--this->winScore;
	}

	this->score = (double)this->winScore / this->visits;

	if (this->parent) {
		this->parent->updateWinnerRecursive(winner);
	}
}
