#pragma once
#include "GameTypes.h"
#include <vector>
#include <memory>
#include "Wall.h"
#include <array>

class Player;


class Game {
private:
	static constexpr int PLAYERS_NUM = 4;
	std::array<std::unique_ptr<Player>, PLAYERS_NUM> players;
	Wall wall;
	GameState state;
	Wind currentTurn;
	std::array<MoveType, PLAYERS_NUM> playersDecisions;


	Player& currentPlayer();
	Player& playerFromWind(Wind wind);


public:
	
	Game(std::unique_ptr<Player> p1,
		std::unique_ptr<Player> p2,
		std::unique_ptr<Player> p3,
		std::unique_ptr<Player> p4);
	const Player& getPlayer(int index) const;
	void dictateWinds();
	void dealInitTiles();
	void update();
	void discardTile(int index);
	void playerMoveFromInput(int index);
	int getTilesLeft() const;
	void nextTurn();
	const Player& getCurrentPlayer();
	GameState getState() const;
	int getPlayerIdFromWind(Wind wind) const;
	int getCurrentPlayerId() const;
	const std::array<std::unique_ptr<Player>, PLAYERS_NUM>& getPlayers() const;
	

};