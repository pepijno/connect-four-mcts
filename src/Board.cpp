#include "Board.hpp"

#include <cassert>

Board::Board(const std::array<uint64_t, 3> board, const uint64_t tops) : board(board), tops(tops) {}

Board Board::empty() {
    const std::array<uint64_t, 3> board = { 0, 0, 0 };
    const uint64_t tops = 0;
    return Board(board, tops);
}

void Board::doMove(const uint8_t column, const Color side) {
    assert(column >= 0);
    assert(column < 8);

    const uint64_t top = this->tops & columns[column];

    this->board[side] |= top;
    this->board[2] |= top;

    this->tops ^= top | (top << 8);
}