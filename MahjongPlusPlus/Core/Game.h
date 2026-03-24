#pragma once
#include "Core/GameTypes.h"
#include "Core/Wall.h"
#include <vector>
#include <memory>
#include <array>
#include "MoveOption.h"

class Player;

/**
 * @brief this class manages the main game logic of a mahjong game.
 * it manages players, turns, wall, discards, and game state.
 */
class Game {
private:

	//-------------------------------------------------------------------------------
	//PRIVATE FIELDS:
	//-------------------------------------------------------------------------------
	
	/**
	 * @brief contains the players in a unique_ptr form to allow for polymorphism.
	 */
	std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM> players;

	/**
	 * @brief where the players draw tiles from.
	 */
	Wall wall;

	/**
	 * @brief for main loop state machine. controls the game flow.
	 */
	GameState state;

	/**
	 * @brief wind of the player currently playing.
	 */
	Wind currentTurn;
	
	/**
	 * @brief the chosen option by each player (such as after a discard pon / chi / skip_
	 */
	std::array<MoveOption, Constants::PLAYERS_NUM> playersDecisions;

	/**
	 * @return a reference to the player who's current turn is.
	 */
	Player& currentPlayer();

	//read only
	const Player& currentPlayer() const;

	/**
	 * @param wind of the desired player.
	 * @return a reference to the player who is assigned to this wind.
	 */
	Player& playerFromWind(Wind wind);

	//read only
	const Player& playerFromWind(Wind wind) const;


public:
	//-------------------------------------------------------------------------------
	//PUBLIC METHODES:
	//-------------------------------------------------------------------------------

	//c'tors:

	/**
	 * @brief initiate a game with a preset wall (mainly for debug purposes)
	 * @param wall desired wall.
	 * @param p1 player0
	 * @param p2 player1
	 * @param p3 player2
	 * @param p4 player3
	 */
	Game(const Wall& wall,
		std::unique_ptr<Player> p1,
		std::unique_ptr<Player> p2,
		std::unique_ptr<Player> p3,
		std::unique_ptr<Player> p4);

	/**
	 * @brief initiate a game with a randomized default wall. 
	 * @param p1 player0
	 * @param p2 player1
	 * @param p3 player2
	 * @param p4 player3
	 */
	Game(std::unique_ptr<Player> p1,
		std::unique_ptr<Player> p2,
		std::unique_ptr<Player> p3,
		std::unique_ptr<Player> p4);

	//methodes:
	
	/**
	 * @brief randomly assigns winds to the players for game initiation purposes.
	 */
	void dictateWinds();

	/**
	 * @brief set players winds manually, for debug purposes.
	 * @param w1 wind1 for player0
	 * @param w2 wind2 for player1
	 * @param w3 wind3 for player2
	 * @param w4 wind4 for player3
	 */
	void dictateWindsChoice(Wind w1, Wind w2, Wind w3, Wind w4);

	/**
	 * @brief deal initial hands to players. first 13 tils go to player0, tiles 14-26 to player1 and so on.
	 */
	void dealInitTiles();
	
	/**
	 * @brief makes the player who's current turn this is to discard a tile from his hand. 
	 * @param index indices 0-12 discard from the hand. index 13 discards the drawn tile.
	 */
	void discardTile(int index);

	/**
	 * @brief moves the current turn wind to the next one. EAST -> SOUTH -> WEST -> NORTH
	 */
	void nextTurn();

	/**
	 * @brief checks if every player has made their decision.
	 * @return false if any player's decided move type is set to MoveType::WAITING.
	 */
	bool haveAllPlayersDecided() const;

	/**
	 * @brief dictates which one of the player's decisions should be played and executes it. 
	 * example: (if one player decided to chi and another player decided to pon the pon should be chosen).
	 * @return the player id of the player who's decision was chosen to be played.
	 */
	int executeDiscardDecision();

	/**
	 * @brief makes the player who's current turn it is to draw a tile from the wall.
	 */
	void draw();

	/**
	 * @brief makes the player who's current turn it is to draw a tile from the dead wall.
	 * replaces the tile drawn with the first tile from the live wall. 
	 *	(the last one which would have been drawn otherwise)
	 */
	void kanDraw();

	/**
	 * @brief resets players decision vector to move options with type MoveType::Waiting.
	 */
	void resetPlayersDecisions();

	/**
	 * @brief depletes each players options vector.
	 */
	void resetPlayersOptions();

	/**
	 * @brief reveals a new dora indicator.
	 */
	void addDora();

	/**
	 * @brief updates the players options vectors to match the last discard made **this turn**. does 
	 * not update the current player's options. 
	 */
	void updatePlayersOptions();


	//-------------------------------------------------------------------------------
	//GETTERS:
	//-------------------------------------------------------------------------------

	/**
	 * @brief returns player by player index.
	 * @param index [0-3], 0 is the human player. 
	 * @return read only access to player.
	 */
	const Player& getPlayer(int index) const;

	/**
	 * @return the amount of drawable tiles left in the game. 
	 */
	int getTilesLeft() const;

	/**
	 * @return read only access to the player who's current turn it is. 
	 */
	const Player& getCurrentPlayer() const;

	/**
	 * @return current game state (see GameState in types for examples)
	 */
	GameState getState() const;

	/**
	 * @param wind of the desired player. 
	 * @return id of the player who is assigned to that wind.
	 */
	int getPlayerIdFromWind(Wind wind) const;

	/**
	 * @return the id of the player who's current turn it is.
	 */
	int getCurrentPlayerId() const;

	/**
	 * @return read only access to the players vector. 
	 */
	const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& getPlayers() const;

	/**
	 * @param playerId of the desired player.
	 * @return the move option from player's decisions vector assigned to that player.
	 */
	const MoveOption& getPlayerDecision(int playerId) const;

	/**
	 * @return read only access to the wall.
	 */
	const Wall& getWall() const;
	

	//-------------------------------------------------------------------------------
	//SETTERS:
	//-------------------------------------------------------------------------------

	/**
	 * @param newState desired new state to set the game to.
	 */
	void setState(GameState newState);
	
	/**
	 * @brief set the decision of a player in the player's decisions vector.
	 * @param playerIndex of the desired player to set the decision for.
	 * @param newOption the option to set it to.
	 */
	void setPlayerDecision(int playerIndex, MoveOption newOption);

	/**
	 * @param turnPlayerWind the wind to set the current turn to.
	 */
	void setTurn(Wind turnPlayerWind);
	
};