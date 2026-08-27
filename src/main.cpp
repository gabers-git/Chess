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

void drawPieces(Board board, Texture2D texture, int squareSize) {

}

int main() {

    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth/8;

    Board board;

    InitWindow(screenWidth, screenHeight, "Chess");

    Texture2D pieceTextures = LoadTexture("../sprites/spritesheet.png");
    SetTextureFilter(pieceTextures, TEXTURE_FILTER_TRILINEAR);
    GenTextureMipmaps(&pieceTextures);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawCheckerboard(0, 0, squareSize, 8, 8, BLACK, WHITE);
        drawPieces(board, pieceTextures, squareSize);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
//g++ main.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
