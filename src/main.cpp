#include "Board.hpp"

int main() {
	Board board = Board::empty();
	board.doMove(3);
	board.doMove(3);
	board.doMove(3);
	board.doMove(2);
	std::cout << board << std::endl;
    return 0;
}
