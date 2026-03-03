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

    for (int s = 0; s < 3; s++) {
        Suit currentSuit = static_cast<Suit>(s);
        for (int v = 1; v <= 10; v++) {
            for (int c = 0; c < 4; c++) {
                wall.emplace_back(currentSuit, v, c);
            }
        }
    }
    for (int v = 1; v <= 7; v++) {
        for (int c = 0; c < 4; c++) {
            wall.emplace_back(static_cast<HonorType>(v), c);
        }
    }
     
    for (auto tile : wall) {
        std::cout << "id= " << tile.getId() << " name: " << tile.getName() << std::endl; 
    }


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Raylib is working! Ready for Mahjong!", 190, 200, 20, DARKGRAY);
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}