#pragma once

#include <cstdint>

struct Board {
    uint64_t piece[12];
    bool turn;
    int moveCounter;
    int epSquare;
    int castling;
};

// Array indices for pieces
enum PieceType {
    WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
};
