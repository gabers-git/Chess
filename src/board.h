#include <cstdint>

struct Board {
    uint64_t piece[12];
    bool turn;
    int moveCounter;
    int epSquare;
    int castling;
};
