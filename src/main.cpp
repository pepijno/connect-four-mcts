#include "Board.hpp"

int main() {
	Board board = Board::empty();
	board.doMove(3, Color::White);
	board.doMove(3, Color::Black);
	board.doMove(3, Color::White);
	board.doMove(2, Color::Black);
	std::cout << board << std::endl;
    return 0;
}
