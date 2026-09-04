#include <cmath>
#include <iostream>
#include "raylib.h"

#include "interact.h"

Vector2 screenToBoard(Vector2 screen, float screenSize, bool orientation) {
    const float x = ceil(screen.x / (screenSize / 8));
    const float y = ceil(screen.y / (screenSize / 8));

    return orientation ? Vector2{7 - x, 7 - y} : Vector2{x, y};
}

void Interact::onClick(float screenSize, bool orientation) {
    const Vector2 mousePos = GetMousePosition();
    const Vector2 boardPos = screenToBoard(mousePos, screenSize, orientation);


}
