#include "Board.hpp"

#include <vector>
#include <memory>

enum class ProvenScore { Win, Loss, Draw, NotProven };

inline std::ostream& operator<<(std::ostream& strm, const ProvenScore& provenScore) {
	if (provenScore == ProvenScore::Win) {
		return strm << "Win";
	}
	if (provenScore == ProvenScore::Loss) {
		return strm << "Loss";
	}
	if (provenScore == ProvenScore::Draw) {
		return strm << "Draw";
	}
	return strm << "NotProven";
}

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
	ProvenScore provenScore;
public:
	Node(Node* parent, const Board& board, const Move move);

	Board getBoard() const { return this->board; };
	Node* getParent() const { return this->parent; };
	ProvenScore getProvenScore() const { return this->provenScore; };

	bool isTerminal() const;
	bool isExpanded() const;
	bool isProven() const;

	Node* expand();
	Node* addChild(const Move move);
	Node* bestChild() const;
	double uct(const int parentVisits) const;

	void updateWinnerRecursive(const Color Winner);
	void updateProvenScoreRecursive(const ProvenScore provenScore);

	void print(std::ostream& os, const int level, const int indent) const;
};
