#include <cstdint>
#include "raylib.h"

#include <string>

#include "board.h"
#include "render.h"
#include "interact.h"

using namespace std;


void resetToStartingPosition(Board& board) {
    // Black Pieces
    board.piece[BLACK_PAWN]   = 0x000000000000FF00ULL;
    board.piece[BLACK_KNIGHT] = 0x0000000000000042ULL;
    board.piece[BLACK_BISHOP] = 0x0000000000000024ULL;
    board.piece[BLACK_ROOK]   = 0x0000000000000081ULL;
    board.piece[BLACK_QUEEN]  = 0x0000000000000008ULL;
    board.piece[BLACK_KING]   = 0x0000000000000010ULL;

    // White Pieces
    board.piece[WHITE_PAWN]   = 0x00FF000000000000ULL;
    board.piece[WHITE_KNIGHT] = 0x4200000000000000ULL;
    board.piece[WHITE_BISHOP] = 0x2400000000000000ULL;
    board.piece[WHITE_ROOK]   = 0x8100000000000000ULL;
    board.piece[WHITE_QUEEN]  = 0x0800000000000000ULL;
    board.piece[WHITE_KING]   = 0x1000000000000000ULL;

    // State Variables
    board.turn = true;          // True for White to move
    board.moveCounter = 0;      // Reset half-move
    board.epSquare = 64;        // No en passant square available (-1 or 64)
    board.castling = 0xF;       // 1111 in binary (Both sides have King & Queen rights)
}

const int screenWidth = 800;
const int screenHeight = 800;
const int squareSize = screenWidth/8;

const bool orientation = true;

Texture2D pieceTextures;
void loadPieceTextures(){
    pieceTextures = LoadTexture("../sprites/spritesheet.png");
    SetTextureFilter(pieceTextures, TEXTURE_FILTER_TRILINEAR);
    GenTextureMipmaps(&pieceTextures);
}

Board board;
Renderer renderer;
Interact interact;



void init(){
    resetToStartingPosition(board);

    InitWindow(screenWidth, screenHeight, "Chess");
    loadPieceTextures();

    SetTargetFPS(60);
}
// //
void update() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        interact.onClick((float)screenWidth, orientation);
    }

    renderer.drawCheckerboard(
        Renderer::CheckerboardParams{
            .posX=0,
            .posY=0,
            .squareSize=squareSize,
            .width=8,
            .height=8,
            .colorOne={ 115, 149, 82, 255 },
            .colorTwo={ 235, 236, 208, 255 },
            .orientation=orientation
        }
    );
    renderer.drawPieces(board, pieceTextures, squareSize, orientation);

    EndDrawing();
}

int main() {

    init();

    while (!WindowShouldClose())
    {
        update();
    }

    CloseWindow();

    return 0;
}
// g++ main.cpp render.cpp interact.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

