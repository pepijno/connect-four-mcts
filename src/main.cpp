#include "Board.hpp"

int main() {
	Board board = Board::empty();
	board.doMove(3);
	board.doMove(3);
	board.doMove(3);
	board.doMove(3);
	board.doMove(3);
	board.doMove(3);
	board.doMove(2);
	std::cout << board << std::endl;

	auto moves = board.moveList();

	for ( const Move move : moves ) {
		std::cout << int(move) << "\n";
	}

    return 0;
}
