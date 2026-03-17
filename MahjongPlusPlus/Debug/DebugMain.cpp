#include "Core/Tile.h"
#include "Core/Wall.h"
#include "Core/Hand.h"
#include "Core/Player.h"
#include "Core/Meld.h"
#include "Core/Triplet.h"
#include "Core/Kan.h"
#include "Core/Game.h"
#include "Input/InputManager.h"
#include "Graphics/Graphics.h"
#include "Graphics/Paths.h"
#include "Input/Controller.h"
#include "Layouts/TileLayouts.h"
#include "raylib.h"
#include "UI/Buttons.h"
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <UI/MeldSelection.h>
#include "Debug/Debug.h"

int main() {
    Button b("PON", Vector2{ 300, 300 }, MoveType::PON);

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "Riichi Mahjong Engine - Test");
    SetTargetFPS(144);


    Graphics graphics;
    graphics.init();

    std::vector<MoveOption> options;
    MoveOption pon1(MoveType::PON, { Debug::tileFromCode("1p",0),Debug::tileFromCode("1p",1) });
    MoveOption pon2(MoveType::PON, { Debug::tileFromCode("3p",0),Debug::tileFromCode("3p",1) });
    options.push_back(pon1);
    options.push_back(pon2);
    MeldSelection meldSelection(options, MoveType::PON);

   

   


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }
        graphics.drawBackground();


        b.draw();


        

        EndDrawing();

    }
        
    
    graphics.clean();
    CloseWindow();
    return 0;
}

