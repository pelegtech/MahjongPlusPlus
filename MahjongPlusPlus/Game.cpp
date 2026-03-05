#include "Game.h"


Game::Game(std::unique_ptr<Player> p1,
	std::unique_ptr<Player> p2,
	std::unique_ptr<Player> p3,
	std::unique_ptr<Player> p4) : 
	players{ std::move(p1),std::move(p2),std::move(p3),std::move(p4) },
	state(GameState::P1_TURN) {
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
	case GameState::WAITING_FOR_INPUT:
		break;
	case GameState::P1_TURN:
		players[0]->Draw(wall);
		state = GameState::WAITING_FOR_INPUT;
		break;
	case GameState::P2_TURN:
		players[1]->Draw(wall);
		players[1]->Discard(13);
		state = GameState::P3_TURN;
		break;
	case GameState::P3_TURN:
		players[2]->Draw(wall);
		players[2]->Discard(13);
		state = GameState::P4_TURN;
		break;
	case GameState::P4_TURN:
		players[3]->Draw(wall);
		players[3]->Discard(13);
		state = GameState::P1_TURN;
		break;
	}

}

void Game::playerMoveFromInput(int index) {
	players[0]->Discard(index);
	state = GameState::P2_TURN;
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