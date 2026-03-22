#pragma once
#include "Core/GameTypes.h"
#include "Core/Wall.h"
#include <vector>
#include <memory>
#include <array>
#include "MoveOption.h"

class Player;


class Game {
private:
	static constexpr int PLAYERS_NUM = 4;
	std::array<std::unique_ptr<Player>, PLAYERS_NUM> players;
	Wall wall;
	GameState state;
	Wind currentTurn;
	std::array<MoveOption, PLAYERS_NUM> playersDecisions;


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
	void discardTile(int index);
	int getTilesLeft() const;
	void nextTurn();
	const Player& getCurrentPlayer();
	GameState getState() const;
	int getPlayerIdFromWind(Wind wind) const;
	int getCurrentPlayerId() const;
	const std::array<std::unique_ptr<Player>, PLAYERS_NUM>& getPlayers() const;
	void setState(GameState newState);
	bool checkingPlayersDecisions();

	//returns the player id of the player  who made the move
	int executeDiscardDecision();
	void draw();
	void setPlayerDecision(int playerIndex, MoveOption newOption);
	void resetPlayersDecisions();
	void resetPlayersOptions();
	void setTurn(Wind turnPlayerWind);

	//updates every players options besides current player
	void updatePlayersOptions();
	const MoveOption& getPlayerDecision(int playerId) const;
	

};