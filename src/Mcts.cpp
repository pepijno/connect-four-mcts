#include "Mcts.hpp"

namespace Mcts {
	void doSimulation(Node& node) {
		Node* n = &node;

		while(!n->isTerminal() && n->isExpanded()) {
			n = n->bestChild();
		}

		if (!n->isTerminal() && !n->isExpanded()) {
			n = n->expand();
		}

		Color winner = Color::Both;
		if (!n->isTerminal()) {
			Board board(n->getBoard());
			board.randomGame();
			winner = board.getWinner();
		} else {
			winner = n->getBoard().getWinner();
		}

		n->updateWinnerRecursive(winner);
	}
}
