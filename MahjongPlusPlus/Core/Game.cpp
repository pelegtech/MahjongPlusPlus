#include "Core/Game.h"
#include "Core/Player.h"
#include "Debug/Debug.h"
#include <utility>
#include <array>
#include <random>
#include <algorithm>
#include <iostream>
#include <string>

Game::Game(const Wall& wall,
	std::unique_ptr<Player> p1,
	std::unique_ptr<Player> p2,
	std::unique_ptr<Player> p3,
	std::unique_ptr<Player> p4) :
	players{ std::move(p1),std::move(p2),std::move(p3),std::move(p4) }, wall(wall),
	state(GameState::TURN_START), currentTurn(Wind::EAST), playersDecisions{} {
}

Game::Game(std::unique_ptr<Player> p1,
	std::unique_ptr<Player> p2,
	std::unique_ptr<Player> p3,
	std::unique_ptr<Player> p4) :
	players{ std::move(p1),std::move(p2),std::move(p3),std::move(p4) },
	state(GameState::TURN_START), currentTurn(Wind::EAST), playersDecisions{} {
}


void Game::dealInitTiles() {
	const int tilesNum = Hand::MAX_HAND_TILES_NUM;
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		std::array<Tile, tilesNum> tiles;
		for (int j = 0; j < tilesNum; j++) {
			tiles[j] = wall.draw();
		}
		Hand newHand(tiles);
		players[i]->initHand(std::move(newHand));
	}
}

const Player& Game::getPlayer(int index) const {
	return *players[index];
}


void Game::discardTile(int index)
{
	currentPlayer().Discard(index);
}



void Game::dictateWinds() {
	std::random_device rd;
	std::mt19937 g(rd());
	std::array<int, 4> order = {0,1,2,3};
	std::shuffle(order.begin(), order.end(), g);
	players[order[0]]->setWind(Wind::EAST);
	players[order[1]]->setWind(Wind::SOUTH);
	players[order[2]]->setWind(Wind::WEST);
	players[order[3]]->setWind(Wind::NORTH);
}

void Game::dictateWindsChoice(Wind w1, Wind w2, Wind w3, Wind w4)
{
	players[0]->setWind(w1);
	players[1]->setWind(w2);
	players[2]->setWind(w3);
	players[3]->setWind(w4);
}

int Game::getTilesLeft() const {
	return wall.tilesLeft();
}

void Game::nextTurn()
{
	Wind nextWind = static_cast<Wind>((static_cast<int>(currentTurn) + 1) % 4);
	Log::add("Changing wind to: " + Debug::windToStr(nextWind));
	currentTurn = nextWind;
}

const Player& Game::getCurrentPlayer()
{
	return currentPlayer();
}

GameState Game::getState() const
{
	return state;
}

int Game::getPlayerIdFromWind(Wind wind) const
{
	for (int i = 0; i < PLAYERS_NUM; i++) {
		if (players[i]->getWind() == wind) {
			return i;
		}
	}
}

int Game::getCurrentPlayerId() const
{
	return getPlayerIdFromWind(currentTurn);
}

const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& Game::getPlayers() const
{
	return players;
}

void Game::setState(GameState newState)
{
	state = newState;
}

bool Game::checkingPlayersDecisions()
{
	int currentPlayerId = getCurrentPlayerId();
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		if (i != currentPlayerId) {
			if (playersDecisions[i].getType() == MoveType::WAITING) {
				return false;
			}
		}
	}
	
	return true;
}

const Wall& Game::getWall() const
{
	return wall;
}

int Game::executeDiscardDecision()
{
	int currentPlayerId = getCurrentPlayerId();
	int skipCounter = 0;

	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		if (i != currentPlayerId && playersDecisions[i].getType() == MoveType::SKIP) {
			skipCounter++;
		}
	}

	if (skipCounter == 3) {
		return currentPlayerId;
	}

	else if (skipCounter == 2) {
		for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
			if (playersDecisions[i].getType() != MoveType::SKIP) {
				if (playersDecisions[i].getType() == MoveType::ANKAN ||
					playersDecisions[i].getType() == MoveType::DAIMINKAN ||
					playersDecisions[i].getType() == MoveType::SHOUMINKAN) {
					wall.addDora();
				}
				players[i]->executeOption(playersDecisions[i],currentPlayer().getDiscards(),currentPlayer().getWind());
				return i;
			}
		}
	}
}

void Game::draw()
{
	Log::add("Player num: " + std::to_string(getCurrentPlayerId()) + " Drew: ");
	currentPlayer().Draw(wall);

}

void Game::setPlayerDecision(int playerIndex, MoveOption newOption)
{
	playersDecisions[playerIndex] = newOption;
}

void Game::resetPlayersDecisions()
{
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		playersDecisions[i] = MoveOption(MoveType::WAITING);
	}
}

void Game::resetPlayersOptions()
{
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		players[i]->resetOptions();
	}
}

void Game::setTurn(Wind turnPlayerWind)
{
	currentTurn = turnPlayerWind;
}

void Game::updatePlayersOptions()
{
	for (int i = 0; i < Constants::PLAYERS_NUM; i++) {
		if (i != getCurrentPlayerId()) {
			players[i]->updateOptionsDiscard(getCurrentPlayer().getLastDiscard(),currentTurn);
		}
	}
}

const MoveOption& Game::getPlayerDecision(int playerId) const
{
	return playersDecisions[playerId];
}




Player& Game::currentPlayer()
{
	return playerFromWind(currentTurn);
}

Player& Game::playerFromWind(Wind wind)
{
	for (const auto& player : players) {
		if (player->getWind() == wind) {
			return *player;
		}
	}
}


