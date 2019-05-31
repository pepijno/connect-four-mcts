#include "Board.hpp"
#include "Mcts.hpp"

int main() {
	Board board = Board::empty();
	board.doMove(3);
	board.doMove(4);
	board.doMove(3);
	board.doMove(0);
	board.doMove(4);
	board.doMove(3);
	board.doMove(3);
	board.doMove(1);
	board.doMove(0);
	board.doMove(0);
	board.doMove(1);
	board.doMove(1);
	board.doMove(6);
	board.doMove(6);
	board.doMove(6);
	board.doMove(1);
	board.doMove(1);
	board.doMove(6);
	board.doMove(0);
	board.doMove(3);
	board.doMove(6);
	board.doMove(3);
	board.doMove(1);
	board.doMove(4);

	std::cout << board << std::endl;

	Node node(nullptr, board, 0);
	for (int i = 0; i < 100000; ++i) {
		Mcts::doSimulation(node);
	}
	node.print(std::cout, 2, 0);

    return 0;
}
