#include "Core/Tile.h"
#include "Core/Wall.h"
#include "Core/Hand.h"
#include "Core/Player.h"
#include "Core/Meld.h"
#include "Core/Debug.h"
#include "Core/Triplet.h"
#include "Core/Kan.h"
#include "Core/Game.h"
#include "Input/InputManager.h"
#include "Graphics/Graphics.h"
#include "Graphics/Paths.h"
#include "Input/Controller.h"
#include "Layouts/TilesLayouts.h"
#include "raylib.h"
#include <array>
#include <memory>
#include <vector>
#include <iostream>


int main() {
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(1920, 1080, "Riichi Mahjong Engine - Test");
    SetTargetFPS(144);
   
    Game game(std::make_unique<Player>(), std::make_unique<Player>()
    ,std::make_unique<Player>(), std::make_unique<Player>());
    Graphics graphics;
    graphics.init();
    
    game.dictateWinds();
    game.dealInitTiles();
    
    InputManager inputManager;
    std::vector<std::unique_ptr<Controller>> controllers;
    controllers.push_back(std::make_unique<HumanController>());
    controllers.push_back(std::make_unique<BotController>());
    controllers.push_back(std::make_unique<BotController>());
    controllers.push_back(std::make_unique<BotController>());
    std::array<PlayerDiscardsLayout, Constants::PLAYERS_NUM> discardsLayouts;


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
            GameDiscardsLayout discardsLayouts(game.getPlayers());
            graphics.drawDiscards(game.getPlayers(), discardsLayouts.layouts);
            graphics.drawHand(((game.getPlayer(0)).getHand()), myHandLayout, myMeldsLayout);
            //discardsLayouts.drawHitBoxes();
            game.update();
        }


        

        
        
        DrawFPS(10, 10);
        EndDrawing();
    }
    graphics.clean();
    CloseWindow();
    return 0;
}