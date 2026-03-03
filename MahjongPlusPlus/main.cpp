#include "raylib.h"
#include "Tile.h"

int main() {
    InitWindow(800, 450, "Riichi Mahjong Engine - Test");
    SetTargetFPS(60);

    Tile testTile("1 Pin");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Raylib is working! Ready for Mahjong!", 190, 200, 20, DARKGRAY);

        DrawText(testTile.GetName().c_str(), 190, 240, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}