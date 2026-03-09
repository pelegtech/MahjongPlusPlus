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

int main() {
    InitWindow(1920, 1080, "Riichi Mahjong Engine - Test");
    SetTargetFPS(60);
   
    Game game(std::make_unique<Player>(), std::make_unique<Player>()
    ,std::make_unique<Player>(), std::make_unique<Player>());
    Graphics graphics;
    graphics.init();
    game.dealInitTiles();
    game.dictateWinds();
    InputManager inputManager(game);
    
  /*  Hand test_hand = Debug::handFromCodes
    ("3p", "1p", "1p", "2p", "3p", "3p", "4p", "5p", "6p", "7p", "8p", "9p", "9p", "9p");
    std::cout << test_hand;
    std::vector<std::unique_ptr<Meld>> melds;
    melds.push_back(Debug::pon("1p"));
    melds.push_back(Debug::ankan("1s"));
    melds.push_back(Debug::shouminkan("2m"));
    melds.push_back(Debug::daiminkan("4p"));
    std::vector<Tile> tiles;
    tiles.push_back(Debug::tileFromCode("5p",0));
    tiles.push_back(Debug::tileFromCode("5p",1));
    Hand test_hand2 = Hand(std::move(tiles),std::move(melds));
    std::cout << test_hand2;*/
    Pon pon1(Debug::tileFromCode("1p", 0), Debug::tileFromCode("1p", 1),
        Debug::tileFromCode("1p", 2), TileMarker::LEFT);
    Pon pon2(Debug::tileFromCode("2s", 0), Debug::tileFromCode("2s", 1),
        Debug::tileFromCode("2s", 2), TileMarker::RIGHT);
    Pon pon3(Debug::tileFromCode("4z", 0), Debug::tileFromCode("4z", 1),
        Debug::tileFromCode("4z", 2), TileMarker::MIDDLE);

    HandTilesRenderer handTilesDebug(AssetPaths::handTiles, AssetPaths::meldTiles);




    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        graphics.drawBackground();
        graphics.drawHand(((game.getPlayer(0)).getHand()));
        graphics.drawDiscards(game.getPlayer(0),
            game.getPlayer(1),
            game.getPlayer(2),
            game.getPlayer(3));
        game.update();

        handTilesDebug.drawPon(pon1, { 500,500 });
        handTilesDebug.drawPon(pon2, { 500,616 });
        handTilesDebug.drawPon(pon3, { 500,732 });

        graphics.drawTilesLeft(game.getTilesLeft());

        int clickedIndex = inputManager.tileIndexFromClick();
        if (clickedIndex != -1) {
            game.playerMoveFromInput(inputManager.tileIndexFromClick());
        }

        EndDrawing();
    }
    graphics.clean();
    CloseWindow();
    return 0;
}