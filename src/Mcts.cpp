#include "Mcts.hpp"

namespace Mcts {
	void doSimulation(Node& node) {
		Node* n = &node;

		while(!n->isTerminal() && n->isExpanded() && !n->isProven()) {
			n = n->bestChild();
		}

		if (!n->isTerminal() && !n->isExpanded() && !n->isProven()) {
			n = n->expand();
		}

		if (n->isProven()) {
			if (!n->getParent()) {
				return;
			}
			const ProvenScore provenScore = n->getProvenScore();
			n->getParent()->updateProvenScoreRecursive(provenScore);
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
