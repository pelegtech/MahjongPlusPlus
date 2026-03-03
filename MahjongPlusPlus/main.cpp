#include "raylib.h"
#include "Tile.h"
#include <vector>
#include <iostream>
 


int main() {
    InitWindow(800, 450, "Riichi Mahjong Engine - Test");
    SetTargetFPS(60);


    //wall for tests
    std::vector<Tile> wall;
    wall.reserve(136);
    for (int i = 0; i < 136; i++) {
        wall.emplace_back(i);
    }
     
    for (auto tile : wall) {
        std::cout << tile;
    }
    //-------------

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Raylib is working! Ready for Mahjong!", 190, 200, 20, DARKGRAY);
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}