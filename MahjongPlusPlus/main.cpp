#include "raylib.h"
#include "Tile.h"
#include <vector>
#include <iostream>
#include "Wall.h"
#include "Hand.h"
#include "Player.h"
#include "Meld.h"
#include "Debug.h"
#include "Triplet.h"
#include "Kan.h"
#include "Game.h"
#include "InputManager.h"
#include "Graphics.h"
#include "Paths.h"
#include "Controller.h"
#include <memory>

int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "Riichi Mahjong Engine - Test");
    SetTargetFPS(144);
   
    Game game(std::make_unique<Player>(), std::make_unique<Player>()
    ,std::make_unique<Player>(), std::make_unique<Player>());
    Graphics graphics;
    graphics.init();
    game.dealInitTiles();
    game.dictateWinds();
    InputManager inputManager;
    std::vector<std::unique_ptr<Controller>> controllers;
    controllers.push_back(std::make_unique<HumanController>());
    controllers.push_back(std::make_unique<BotController>());
    controllers.push_back(std::make_unique<BotController>());
    controllers.push_back(std::make_unique<BotController>());



    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }


        
        
        
       

        if (game.getState() == GameState::WAITING_FOR_DRAW_INPUT) {
            int currentPlayerId = game.getCurrentPlayerId();
            const Hand& currentHand = game.getCurrentPlayer().getHand();
            HandTilesLayout layout(currentHand);
            int chosenTileIndex =  
                controllers[currentPlayerId]->decideDiscard(currentHand,layout,inputManager);
            if (chosenTileIndex != -1) {
                game.discardTile(chosenTileIndex);
            }
        }
        if (game.getState() == GameState::GAME_END) {
            ClearBackground(RAYWHITE);
            DrawText("GAME OVER NO MORE TILES", 500, 500, 50, BLACK);
            DrawText("press escape to quit", 500, 550, 20, RED);

        }
        else {
            graphics.drawBackground();
            graphics.drawWinds(game.getPlayer(0).getWind());
            graphics.drawTilesLeft(game.getTilesLeft());
            HandTilesLayout myHandLayout(game.getPlayer(0).getHand());
            MeldsLayout myMeldsLayout(game.getPlayer(0).getHand().getMelds());
            graphics.drawHand(((game.getPlayer(0)).getHand()), myHandLayout, myMeldsLayout);
            graphics.drawDiscards(game.getPlayer(0),
                game.getPlayer(1),
                game.getPlayer(2),
                game.getPlayer(3));
            game.update();
        }


        

        
        
        DrawFPS(10, 10);
        EndDrawing();
    }
    graphics.clean();
    CloseWindow();
    return 0;
}