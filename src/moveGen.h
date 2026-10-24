#pragma once

#include "board.h"

#include <cstdint>
#include <raylib.h>

struct MoveFlag
{
    static constexpr int None = 0;                  //quiet Move
    static constexpr int PawnDoublePush = 1;
    static constexpr int CastleKingSide = 2;
    static constexpr int CastleQueenSide = 3;
    static constexpr int Capture = 4;
    static constexpr int EnPassantCapture = 5;

    //promotion
    static constexpr int PromoteKnight = 8;
    static constexpr int PromoteBishop = 9;
    static constexpr int PromoteRook = 10;
    static constexpr int PromoteQueen = 11;

    //promotion with capture
    static constexpr int PromoteKnightCapture = 12;
    static constexpr int PromoteBishopCapture = 13;
    static constexpr int PromoteRookCapture = 14;
    static constexpr int PromoteQueenCapture = 15;

    //masks for faster checking
    static constexpr int PromotionMask = 8; // 1000 binary
    static constexpr int CaptureMask = 4;   // 0100 binary
};

struct Move
{
    //raw data
    uint16_t Value;

    Move(int from, int to, int flag)
    {
        Value = (uint16_t)((to & 0x3F) | ((from & 0x3F) << 6) | ((flag & 0xF) << 12));

    };

    //helper variables

    //decoding
    int EndingPos() const   { return Value & 0x3F; }
    int StartingPos() const { return (Value >> 6) & 0x3F; }
    int Flag() const        { return (Value >> 12) & 0xF; }

    //flag checks
    bool IsCapture() const    { return (Flag() & MoveFlag::CaptureMask) != 0;  }
    bool IsPromotion() const  { return (Flag() & MoveFlag::PromotionMask) != 0; }

};

class moveGen {

public:

    Move* generate(Board* board, Move* moveList);

    void generatePawnMoves(Board* board);
}
