#include "Board.hpp"

#include <queue>

class Node {
private:
	Board board;
	std::queue<Move> movesLeft;
	std::vector<Node> children;
public:
	Node(const Board& board);
};
