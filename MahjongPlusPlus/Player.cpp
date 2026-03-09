#include "Player.h"

MoveOption::MoveOption(MoveType type, std::vector<Tile> tiles) :
	type(type), tiles(std::move(tiles)) {
	if (type == MoveType::PON && tiles.size() != 2) {
		throw invalidOption();
	}
	if (type == MoveType::CHI && tiles.size() != 2) {
		throw invalidOption();
	}
	if (type == MoveType::ANKAN && tiles.size() != 4) {
		throw invalidOption();
	}
	if (type == MoveType::DAIMINKAN && tiles.size() != 3) {
		throw invalidOption();
	}
	if (type == MoveType::PON && tiles.size() != 1) {
		throw invalidOption();
	}
	if (type == MoveType::TSUMO && tiles.size() != 0) {
		throw invalidOption();
	}
	if (type == MoveType::RON && tiles.size() != 1) {
		throw invalidOption();
	}
	if (type == MoveType::RIICHI && tiles.size() != 1) {
		throw invalidOption();
	}
	if (type == MoveType::DISCARD && tiles.size() != 1) {
		throw invalidOption();
	}
}



void Player::Draw(Wall& wall) {
	hand.drawTile(wall.draw());
}

void Player::setWind(Wind wind) {
	this->wind = wind;
}
void Player::setScore(int score) {
	this->score = score;
}

void Player::Discard(int index) {
	
	if (index == hand.tilesNum() - 1) {
		hand.discardDrawnTile(discards);
	}
	else {
		hand.discardHandTile(discards,index);
		hand.addDrawnTile();
	}


}

void Player::sortHand() {
	hand.sortHand();
}

const Hand& Player::getHand() const {
	return hand;
}

const Discards& Player::getDiscards() const {
	return discards;
}

const Wind& Player::getWind() const {
	return wind;
}


//void Player::Draw(Wall& wall){}
//bool tenpai();
//std::vector<MoveOption> Player::riichiOptions() const{}
//std::vector<MoveOption> Player::ponOptions(Tile discardedTile) const{}
//std::vector<MoveOption> Player::chiOptions(Tile discardedTile) const{}
//std::vector<MoveOption> Player::kanOptions(Tile discardedTile) const{}
//MoveOption Player::chosenMove(const std::vector<MoveOption>& options) const{}
//void Player::playRiichi(const MoveOption& option){}
//void Player::playTsumo(const MoveOption& option){}
//void Player::playRon(const MoveOption& option){}
//void Player::playDiscard(const MoveOption& option){}
//void Player::playPon(const MoveOption& option, Tile discardedTile, Wind otherWind){}
//void Player::playChi(const MoveOption& option, Tile discardedTile, Wind otherWind){}
//void Player::playAnkan(const MoveOption& option, Wall& wall){}
//void Player::playDaiminkan(const MoveOption& option, Tile discardedTile, Wind otherWind, Wall& wall){}
//void Player::playShouminkan(const MoveOption& option, Wall& wall){}