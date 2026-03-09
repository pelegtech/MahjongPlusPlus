#include "Player.h"
#include "Triplet.h"
#include "Meld.h"
#include "Kan.h"



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
	
	if (index == hand.freeTilesNum() - 1) {
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

TileMarker Player::relativePlace(Wind otherWind) {
	int relativePosition = (static_cast<int>(wind)
		- static_cast<int>(otherWind) + PLAYERS_NUM) % PLAYERS_NUM;
	return static_cast<TileMarker>(relativePosition);
}


//options:

bool Player::ponOptions(const Tile& discard) {
	int counter = 0;
	Tile option[3];
	//count the number of equal tiles
	for (int i = 0; i < hand.freeTilesNum(); i++) {
		if (counter < 3) {
			if (Tile::isEqual(discard, hand[i])) {
				option[counter++] = hand[i];
			}
		}
	}
	//in the case of akadora display two options one with aka one without. 
	//hand must be sorted by id for this to work consistently.
	if (counter == 3 && discard.getValue() == 5 &&
		discard.getSuit() != Suit::HONOR && discard.isAkadora() != true) {
		options.push_back(MoveOption(MoveType::PON, { option[0],option[1] }));
		options.push_back(MoveOption(MoveType::PON, { option[1],option[2] }));
		return true;

		//normal case of no aka.
	} else if (counter == 2 || counter == 3) {
		options.push_back(MoveOption(MoveType::PON, { option[0],option[1] }));
		return true;
	} //if not enough tiles were found.
	else {
		return false;
	}
}

void Player::executePon(const MoveOption& chosenOption,
	Discards& discards, const Wind& otherWind) {
	hand.createTriplet<Pon>(discards, chosenOption.tiles[0],
		chosenOption.tiles[1], relativePlace(otherWind));
}