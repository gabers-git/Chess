#pragma once

#include "raylib.h"

#include <unordered_map>
#include <string>

#include "board.h"

using namespace std;

class Renderer {

public:
    void drawCheckerboard(int posX, int posY,
                      int squareSize,
                      int width, int height,
                      Color colorOne, Color colorTwo);
    void drawPiece(int posX, int posY, Texture2D texture, int size, string piece);
    void drawPieceBitboard(uint64_t board, Texture2D texture, int squareSize, string piece);
    void drawPieces(const Board& board, Texture2D texture, int squareSize);
};
