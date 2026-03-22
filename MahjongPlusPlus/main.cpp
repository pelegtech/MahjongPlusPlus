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
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <array>
#include "Graphics/TileGraphics.h"
#include "UI/CallSelection.h"
#include "UI/MeldSelection.h"
#include "Debug/Debug.h"
#include <exception>

int main() {
    try {

        Log::init();
        SetConfigFlags(FLAG_WINDOW_UNDECORATED);
        InitWindow(1920, 1080, "Mahjong Plus Plus debug main");
        //SetTargetFPS(144);

        //initialize graphics

        Graphics graphics;
        graphics.init();

        //initialize controllers. controller 0 is the human player.
        std::array< std::unique_ptr<Controller>, 4> controllers;
        controllers[0] = std::make_unique<HumanController>();
        controllers[1] = std::make_unique<BotController>();
        controllers[2] = std::make_unique<BotController>();
        controllers[3] = std::make_unique<BotController>();

        //initialize game players. player 0 is the perspective human player.
        Game game(
            std::make_unique<Player>(),
            std::make_unique<Player>(),
            std::make_unique<Player>(),
            std::make_unique<Player>()
        );

        //ui and input managers
        InputManager inputManager;
        CallSelection callSelection;
        MeldSelection meldSelection;
        bool justEnteredState = true;
        UIState currentUIState = UIState::HIDDEN;
        MoveType pendingCallType = MoveType::WAITING;

        //game init
        game.dictateWinds();
        game.setState(GameState::INIT_ROUND);

        //debug mode 
        bool debugMode = false;

        //delday between turns
        float delayTime = 0.0f;
        const float BOT_DELAY_TIME = 0.3f;
        const float TURN_END_DELAY = 0.2F;

        while (!WindowShouldClose()) {
            GameState currentGameState = game.getState();
            const Player& humanPlayer = game.getPlayer(0);


            switch (currentGameState) {

            case GameState::INIT_ROUND:
                game.dealInitTiles();
                game.setState(GameState::TURN_START);
                break;

            case GameState::TURN_START: {
                pendingCallType = MoveType::WAITING;
                game.resetPlayersDecisions();
                game.resetPlayersOptions();
                int currentPlayerTileCount = game.getCurrentPlayer().getHand().legalHandSize();

                if (game.getTilesLeft() == 0) {
                    game.setState(GameState::GAME_OVER);
                }
                else {

                    if (currentPlayerTileCount == Hand::MAX_HAND_SIZE) {
                        game.setState(GameState::WAITING_FOR_TURN_ACTION);
                    }
                    else if (currentPlayerTileCount == (Hand::MAX_HAND_SIZE - 1)) {
                        game.setState(GameState::DRAW);
                    }
                    else {
                        throw Hand::illegalHandSize();
                    }
                }
                break;
            }
            case GameState::DRAW:
                game.draw();
                game.setState(GameState::WAITING_FOR_TURN_ACTION);
                break;
            case GameState::WAITING_FOR_TURN_ACTION: {
                int currentPlayerId = game.getCurrentPlayerId();
                HandTilesLayout currentPlayerLayout(game.getCurrentPlayer().getHand());
                int chosenDiscardId = controllers[currentPlayerId]->decideDiscard(currentPlayerLayout, inputManager);

                if (chosenDiscardId != -1) {
                    game.discardTile(chosenDiscardId);
                    for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
                        if (i != currentPlayerId) {
                            game.updatePlayersOptions();
                        }
                    }
                    game.setState(GameState::WAITING_FOR_DISCARD_DECISIONS);
                }

                break;
            }

            case GameState::WAITING_FOR_DISCARD_DECISIONS:
            {
                if (justEnteredState) {
                    if (humanPlayer.getOptions().empty()) {
                        game.setPlayerDecision(0, MoveOption(MoveType::SKIP));
                    }
                    else if (currentUIState != UIState::SELECTING_MELD) {
                        callSelection.update(humanPlayer.getOptions());
                        currentUIState = UIState::SELECTING_TYPE;
                    }
                }

                if (currentUIState == UIState::SELECTING_TYPE) {
                    MoveType clickedType = controllers[0]->decideTypeAfterDiscard(inputManager, callSelection);
                    if (clickedType == MoveType::SKIP) {
                        game.setPlayerDecision(0, MoveOption(MoveType::SKIP));
                        currentUIState = UIState::HIDDEN;
                    }
                    else if (clickedType != MoveType::WAITING) {
                        pendingCallType = clickedType;
                        meldSelection.update(humanPlayer.getOptions(), pendingCallType);
                        currentUIState = UIState::SELECTING_MELD;
                    }
                }
                else if (currentUIState == UIState::SELECTING_MELD) {
                    MoveOption clickedOption = controllers[0]->decideOptionAfterDiscard(inputManager, meldSelection);
                    if (clickedOption.getType() != MoveType::WAITING) {
                        game.setPlayerDecision(0, clickedOption);
                        currentUIState = UIState::HIDDEN;
                    }
                }
                for (int i = 1; i < 4; i++) {
                    MoveOption botMove = controllers[i]->decideOptionAfterDiscard(inputManager, meldSelection);
                    game.setPlayerDecision(i, botMove);
                }
                if (game.checkingPlayersDecisions()) {
                    int playerWhoMadeMoveId = game.executeDiscardDecision();
                    if (playerWhoMadeMoveId == game.getCurrentPlayerId()) {
                        game.nextTurn();
                        game.setState(GameState::TURN_START);
                    }
                    else {
                        game.setTurn(game.getPlayer(playerWhoMadeMoveId).getWind());
                        game.setState(GameState::TURN_START);
                    }
                }
            }
            break;

            case (GameState::GAME_OVER):
                break;

            }



            //drawing

            BeginDrawing();

            if (game.getState() == GameState::GAME_OVER) {
                ClearBackground(RAYWHITE);
                DrawText("GAME OVER NO MORE TILES", 500, 500, 50, BLACK);
                DrawText("press escape to quit", 500, 550, 20, RED);

            }
            else {

                ClearBackground(RAYWHITE);
                if (IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }




                //drawing basic elements:
                graphics.drawBackground();
                graphics.drawWinds(humanPlayer.getWind());
                graphics.drawTilesLeft(game.getTilesLeft());



                //drawing discards:
                GameDiscardsLayout discardsLayout(game.getPlayers());
                graphics.drawDiscards(game.getPlayers(), discardsLayout.layouts);
                graphics.highlightLastDiscard(discardsLayout.getPlayersLayout(game.getCurrentPlayerId()));

                HandTilesLayout humanHandLayout(humanPlayer.getHand());
                MeldsLayout humanMeldsLayout(humanPlayer.getHand().getMelds());
                graphics.drawHand(humanPlayer.getHand(), humanHandLayout, humanMeldsLayout);



                if (currentGameState == GameState::WAITING_FOR_DISCARD_DECISIONS) {
                    if (currentUIState == UIState::SELECTING_TYPE) {
                        callSelection.draw();
                    }
                    else if (currentUIState == UIState::SELECTING_MELD) {
                        meldSelection.draw(graphics.getDiscardRenderer());
                    }
                }

                if (IsKeyPressed(KEY_F3)) {
                    debugMode = !debugMode;
                }
                if (debugMode) {
                    Vector2 mousePos(GetMousePosition());
                    graphics.drawTileHitBox(humanHandLayout);
                    graphics.drawDiscardsHitboxes(discardsLayout);
                    DrawText(TextFormat("%.0f,%.0f", mousePos.x, mousePos.y), mousePos.x + 15, mousePos.y, 20, RED);
                    DrawFPS(10, 10);
                }
            }
            EndDrawing();
        }

        graphics.clean();
        CloseWindow();
    }
    catch (const std::exception& e) {
        Log::add("EXCEPTION FOUND: " + std::string(e.what()));
    }
    return 0;
}