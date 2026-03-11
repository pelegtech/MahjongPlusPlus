#include "Game.h"


Game::Game(std::unique_ptr<Player> p1,
	std::unique_ptr<Player> p2,
	std::unique_ptr<Player> p3,
	std::unique_ptr<Player> p4) :
	players{ std::move(p1),std::move(p2),std::move(p3),std::move(p4) },
	state(GameState::DRAW), currentTurn(Wind::EAST)
{
	playersDecisions.fill(MoveType::WAITING);
}

void Game::dealInitTiles() {
	for (int i = 0; i < Hand::MAX_HAND_SIZE - 1; i++) {
		for (int j = 0; j < PLAYERS_NUM; j++) {
			players[j]->Draw(wall);
			
		}
	}	
	for (int j = 0; j < PLAYERS_NUM; j++) {
		players[j]->sortHand();

	}
}

const Player& Game::getPlayer(int index) const {
	return *players[index];
}

void Game::update(){
	switch (state) {
	case GameState::DRAW:
		if (wall.tilesLeft() == 0) {
			state = GameState::GAME_END;
			break;
		}
		currentPlayer().Draw(wall);
		state = GameState::WAITING_FOR_DRAW_INPUT;
		break;

	case GameState::WAITING_FOR_DRAW_INPUT:
		break;
	}
	

}

void Game::discardTile(int index)
{
	currentPlayer().Discard(index);
	//change later
	nextTurn();
	state = GameState::DRAW;
}

void Game::playerMoveFromInput(int index) {
	
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

int Game::getTilesLeft() const {
	return wall.tilesLeft();
}

void Game::nextTurn()
{
	Wind nextWind = static_cast<Wind>((static_cast<int>(currentTurn) + 1) % 4);
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


