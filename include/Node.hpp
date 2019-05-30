#include "Board.hpp"

#include <vector>

class Node {
private:
	Node* parent;

	Board board;
	std::vector<Move> moves;
	std::vector<Node> children;

	float score;
	int visits;
	int winScore;
public:
	Node(Node* parent, const Board& board);

	bool isTerminal() const;
	bool isExpanded() const;

	Node expand();
	Node addChild(const Move move);
	Node bestChild() const;
	double uct(const int parentVisits) const;
};
