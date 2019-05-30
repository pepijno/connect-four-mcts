#include "Board.hpp"

#include <queue>

class Node {
private:
	Board board;
	std::queue<Move> movesLeft;
	std::vector<Node> children;

	float score;
	int visits;
	int winScore;
public:
	Node(const Board& board);
};
