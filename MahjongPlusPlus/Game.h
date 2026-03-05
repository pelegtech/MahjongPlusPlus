#pragma once
#include "Discards.h"
#include "Wall.h"
#include "Hand.h"
#include "Tile.h"
#include "Player.h"
#include "GameTypes.h"
#include <vector>
#include "Wall.h"
#include "raylib.h"

enum class GameState {
	WAITING_FOR_INPUT,
	P1_TURN,
	P2_TURN,
	P3_TURN,
	P4_TURN,
};

class Game {
private:
	static constexpr int PLAYERS_NUM = 4;
	std::array<std::unique_ptr<Player>, PLAYERS_NUM> players;
	Wall wall;
	GameState state;
public:
	
	Game(std::unique_ptr<Player> p1,
		std::unique_ptr<Player> p2,
		std::unique_ptr<Player> p3,
		std::unique_ptr<Player> p4);
	const Player& getPlayer(int index) const;
	void dictateWinds();
	void dealInitTiles();
	void update();
	void playerMoveFromInput(int index);
	int getTilesLeft() const;

};