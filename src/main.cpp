#include <iostream>
#include <cmath>
#include <cstdint>
#include "raylib.h"

#include <unordered_map>
#include <string>

#include "board.h"

using namespace std;

std::unordered_map<std::string, Rectangle> pieceTextureLookup = {
    {"w-king", {0, 0, 480, 480}},
    {"w-queen", {480, 0, 480, 480}},
    {"w-rook", {960, 0, 480, 480}},
    {"w-knight", {1440, 0, 480, 480}},
    {"w-bishop", {1920, 0, 480, 480}},
    {"w-pawn", {2400, 0, 480, 480}},
    {"b-king", {0, 480, 480, 480}},
    {"b-queen", {480, 480, 480, 480}},
    {"b-rook", {960, 480, 480, 480}},
    {"b-knight", {1440, 480, 480, 480}},
    {"b-bishop", {1920, 480, 480, 480}},
    {"b-pawn", {2400, 480, 480, 480}},
};


void resetToStartingPosition(Board& board) {
    // White Pieces
    board.piece[WHITE_PAWN]   = 0x000000000000FF00ULL; // Rank 2
    board.piece[WHITE_KNIGHT] = 0x0000000000000042ULL; // B1, G1
    board.piece[WHITE_BISHOP] = 0x0000000000000024ULL; // C1, F1
    board.piece[WHITE_ROOK]   = 0x0000000000000081ULL; // A1, H1
    board.piece[WHITE_QUEEN]  = 0x0000000000000008ULL; // D1
    board.piece[WHITE_KING]   = 0x0000000000000010ULL; // E1

    // Black Pieces
    board.piece[BLACK_PAWN]   = 0x00FF000000000000ULL; // Rank 7
    board.piece[BLACK_KNIGHT] = 0x4200000000000000ULL; // B8, G8
    board.piece[BLACK_BISHOP] = 0x2400000000000000ULL; // C8, F8
    board.piece[BLACK_ROOK]   = 0x8100000000000000ULL; // A8, H8
    board.piece[BLACK_QUEEN]  = 0x0800000000000000ULL; // D8
    board.piece[BLACK_KING]   = 0x1000000000000000ULL; // E8

    // State Variables
    board.turn = true;          // True for White to move
    board.moveCounter = 0;      // Reset half-move / full-move clock
    board.epSquare = -1;        // No en passant square available (-1 or 64)
    board.castling = 0xF;       // 1111 in binary (Both sides have King & Queen rights)
}


void drawCheckerboard(int posX, int posY,
                      int squareSize,
                      int width, int height,
                      Color colorOne, Color colorTwo)
{
    bool usingColorOne = false;

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {
            DrawRectangle(posX + (x * squareSize), posY + (y * squareSize), squareSize, squareSize, usingColorOne ? colorOne : colorTwo);

            usingColorOne = !usingColorOne;
        }

        usingColorOne = !usingColorOne;
    }
}

void drawPiece(int posX, int posY, Texture2D texture, int size, string piece) {
    const Rectangle rect = pieceTextureLookup[piece];
    DrawTexturePro(texture, rect, {(float)posX, (float)posY, (float)size, (float)size}, {0,0}, 0, WHITE);
}

void drawPieceBitboard(uint64_t board, Texture2D texture, int squareSize, string piece) {
    for (int square = 0; square < 64; square++) {
        if ((board & (1ULL << square)) != 0) {
            int x = square % 8;
            int y = square / 8;

            drawPiece(x*squareSize, y*squareSize, texture, squareSize, piece);
        }
    }
}

void drawPieces(Board board, Texture2D texture, int squareSize){
    drawPieceBitboard(board.piece[0], texture, squareSize, "w-pawn");
    drawPieceBitboard(board.piece[1], texture, squareSize, "w-knight");
    drawPieceBitboard(board.piece[2], texture, squareSize, "w-bishop");
    drawPieceBitboard(board.piece[3], texture, squareSize, "w-rook");
    drawPieceBitboard(board.piece[4], texture, squareSize, "w-queen");
    drawPieceBitboard(board.piece[5], texture, squareSize, "w-king");

    drawPieceBitboard(board.piece[6], texture, squareSize, "b-pawn");
    drawPieceBitboard(board.piece[7], texture, squareSize, "b-knight");
    drawPieceBitboard(board.piece[8], texture, squareSize, "b-bishop");
    drawPieceBitboard(board.piece[9], texture, squareSize, "b-rook");
    drawPieceBitboard(board.piece[10], texture, squareSize, "b-queen");
    drawPieceBitboard(board.piece[11], texture, squareSize, "b-king");
}

int main() {

    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth/8;

    Board board;
    resetToStartingPosition(board);

    InitWindow(screenWidth, screenHeight, "Chess");

    Texture2D pieceTextures = LoadTexture("../sprites/spritesheet.png");
    SetTextureFilter(pieceTextures, TEXTURE_FILTER_TRILINEAR);
    GenTextureMipmaps(&pieceTextures);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawCheckerboard(0, 0, squareSize, 8, 8, { 115, 149, 82, 255 }, { 235, 236, 208, 255 });
        drawPieces(board, pieceTextures, squareSize);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
//g++ main.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
