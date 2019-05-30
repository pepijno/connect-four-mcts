#include "Board.hpp"

#include <vector>
#include <memory>

class Node {
private:
	Node* parent;

	Board board;
	Move move;
	std::vector<Move> moves;
	std::vector<std::unique_ptr<Node>> children;

	float score;
	int visits;
	int winScore;
public:
	Node(Node* parent, const Board& board, const Move move);

	Board getBoard() const { return this->board; };

	bool isTerminal() const;
	bool isExpanded() const;

	Node* expand();
	Node* addChild(const Move move);
	Node* bestChild() const;
	double uct(const int parentVisits) const;

	void updateWinnerRecursive(const Color Winner);

	void print(std::ostream& os, const int level, const int indent) const;
};
