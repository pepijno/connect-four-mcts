#include "Board.hpp"

#include <vector>

class Node {
private:
	Node* parent;

	Board board;
	std::vector<Move> movesLeft;
	std::vector<Node> children;

	float score;
	int visits;
	int winScore;
public:
	Node(Node* parent, const Board& board);
};
