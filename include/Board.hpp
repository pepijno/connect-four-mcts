#pragma once

#include <array>
#include <cstdint>

const std::array<uint64_t, 8> columns = {
    0x0101010101010101,
    0x0202020202020202,
    0x0404040404040404,
    0x0808080808080808,
    0x1010101010101010,
    0x2020202020202020,
    0x4040404040404040,
    0x8080808080808080
};

enum Color { WHITE = 0, BLACK = 1, BOTH = 2 };

class Board
{
private:
    std::array<uint64_t, 3> board;
    uint64_t tops;
public:
    Board(const std::array<uint64_t, 3> board, const uint64_t tops);
    static Board empty();

    void doMove(const uint8_t column, const Color side);
};