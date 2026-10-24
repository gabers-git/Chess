#include <iostream>
#include <cmath>
#include <cstdint>
#include "raylib.h"

#include <unordered_map>
#include <string>

#include "board.h"
#include "render.h"

using namespace std;

unordered_map<string, Rectangle> pieceTextureByName = {
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

void Renderer::drawCheckerboard(const CheckerboardParams& params){


    bool usingColorOne = params.orientation ? false : true;

    for (int y = 0; y < params.height; y++) {

        for (int x = 0; x < params.width; x++) {
            DrawRectangle(params.posX + (x * params.squareSize), params.posY + (y * params.squareSize), params.squareSize, params.squareSize, usingColorOne ? params.colorOne : params.colorTwo);

            usingColorOne = !usingColorOne;
        }

        usingColorOne = !usingColorOne;
    }
                      }

void Renderer::drawPiece(int posX, int posY, Texture2D texture, int size, string piece) {
    const Rectangle rect = pieceTextureByName[piece];
    DrawTexturePro(texture, rect, {(float)posX, (float)posY, (float)size, (float)size}, {0,0}, 0, WHITE);
}

void Renderer::drawPieceBitboard(uint64_t board, Texture2D texture, int squareSize, string piece, bool orientation) {
    for (int square = 0; square < 64; square++) {
        if ((board & (1ULL << square)) != 0) {
            int x = orientation ? 7 - (square % 8) : square % 8;
            int y = orientation ? 7 - (square / 8) : square / 8;

            drawPiece(x*squareSize, y*squareSize, texture, squareSize, piece);
        }
    }
}
void Renderer::drawPieces(const Board& board, Texture2D texture, int squareSize, bool orientation){
    drawPieceBitboard(board.piece[0], texture, squareSize, "w-pawn", orientation);
    drawPieceBitboard(board.piece[1], texture, squareSize, "w-knight", orientation);
    drawPieceBitboard(board.piece[2], texture, squareSize, "w-bishop", orientation);
    drawPieceBitboard(board.piece[3], texture, squareSize, "w-rook", orientation);
    drawPieceBitboard(board.piece[4], texture, squareSize, "w-queen", orientation);
    drawPieceBitboard(board.piece[5], texture, squareSize, "w-king", orientation);

    drawPieceBitboard(board.piece[6], texture, squareSize, "b-pawn", orientation);
    drawPieceBitboard(board.piece[7], texture, squareSize, "b-knight", orientation);
    drawPieceBitboard(board.piece[8], texture, squareSize, "b-bishop", orientation);
    drawPieceBitboard(board.piece[9], texture, squareSize, "b-rook", orientation);
    drawPieceBitboard(board.piece[10], texture, squareSize, "b-queen", orientation);
    drawPieceBitboard(board.piece[11], texture, squareSize, "b-king", orientation);
}

