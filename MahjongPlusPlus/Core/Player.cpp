#include "Core/Player.h"
#include "Core/Triplet.h"
#include "Core/Meld.h"
#include "Core/Kan.h"
#include <iostream>
#include "Tile.h"
#include "Debug/Debug.h"


void Player::Draw(Wall& wall) {
	hand.drawTile(wall.draw());
}

void Player::kanDraw(Wall& wall)
{
	hand.drawTile(wall.kanDraw());
}

void Player::addTileFromWall(Wall& wall)
{
	hand.addTile(wall.draw());
}

void Player::setWind(Wind wind) {
	this->wind = wind;
}
void Player::setScore(int score) {
	this->score = score;
}

void Player::Discard(int index) {
	
	if (index == hand.getHandTilesNum()) {
		hand.discardDrawnTile(discards);
	}
	else {
		if (hand.isHoldingDrawnTile()) {
			hand.discardHandTile(discards, index);
			hand.addDrawnTile();
		}
		else {
			hand.discardHandTile(discards, index);
		}
	}
}

void Player::sortHand() {
	hand.sortHand();
}

const Hand& Player::getHand() const {
	return hand;
}

Discards& Player::getDiscards() {
	return discards;
}

const Discards& Player::getDiscards() const
{
	return discards;
}


const Wind& Player::getWind() const {
	return wind;
}

const Tile& Player::getLastDiscard() const
{
	return discards.getLastDiscard();
}

TileMarker Player::relativeMarker(Wind otherWind) const{
	int relativePosition = (static_cast<int>(wind)
		- static_cast<int>(otherWind) + Constants::PLAYERS_NUM) % Constants::PLAYERS_NUM;
	return static_cast<TileMarker>(relativePosition);
}




//options:

void Player::executeOption(const MoveOption& option, Discards& discards ,const Wind& otherWind)
{
	switch (option.getType()) {
	case(MoveType::PON):
		executePon(option, discards, otherWind);
		//log-------------
		Log::add("p0 called pon, hand: ");
		Log::add(hand.handToString());
		//---------------
		break;
	case(MoveType::CHI):
		executeChi(option, discards, otherWind);
		//log-------------
		Log::add("p0 called chi, hand: ");
		Log::add(hand.handToString());
		//---------------
		break;
	case(MoveType::DAIMINKAN):
		executeDaiminkan(option, discards, otherWind);
		//log-------------
		Log::add("p0 called kan, hand: ");
		Log::add(hand.handToString());
		//---------------
	}
}

bool Player::ponOptions(const Tile& discard) {
	int counter = 0;
	Tile option[3];
	//count the number of equal tiles
	for (int i = 0; i < hand.getHandTilesNum(); i++) {
		if (counter < 3) {
			if (Tile::isEqual(discard, hand.getHandTile(i))) {
				option[counter++] = hand.getHandTile(i);
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
		chosenOption.tiles[1], relativeMarker(otherWind));
}

bool Player::chiOptions(const Tile& discard, const Wind& wind)
{
	if (getRelativePosition(wind) != RelativePosition::LEFT) {
		return 0;
	}

	std::array<int, 4> foundId; //this will show the hand id of found 2 away adjacent tiles to the discard tile.
	foundId.fill(-1);
	bool akadoraCase = false;
	bool flag = false;
	int discardValue = discard.getValue();
	Suit discardSuit = discard.getSuit();

	//can't make a chi with an honor tile.
	if (discardSuit == Suit::HONOR) {
		return false;
	}
	
	//go over hand tiles to find if they are 2 tile adjacent to the discarded tile.
	for (int i = 0; i < hand.getHandTilesNum(); i++) {
		Tile currentTile = hand.getHandTile(i);
		if (currentTile.getSuit() != discardSuit) {
			continue;
		}
		for (int j = -2; j <= 2; j++) {
			if (j != 0) {
				if (currentTile.getValue() == discardValue + j) {
					int index = j + 2 - (j > 0); // maps the numbers {-2,-1,1,2} to {0,1,2,3} respectively for easy array insertion.

					//checks if an akadora tile was overwritten by a non akadora so that both options will be accounted for.
					if (foundId[index] != -1 && hand.getHandTile(foundId[index]).isAkadora()) {
						akadoraCase = true; 
					}
					foundId[index] = i;
				}
			}
		}
	}

	//this loop goes over the found 2 away adjacent tiles and if there are two adjacent ones they will be 
	//counted as a chi along with  the discarded tile.
	for (int i = 0; i < 3; i++) {
		if (foundId[i] != -1 && foundId[i + 1] != -1) { 
			options.push_back(MoveOption(MoveType::CHI, { hand.getHandTile(foundId[i]),hand.getHandTile(foundId[i + 1]) }));
			flag = true;
			if (akadoraCase) { //in case of akadora we make the same option with an akadora tile that was overwritten earlier.
				if (hand.getHandTile(foundId[i]).getValue() == 5) {
					options.push_back(
						MoveOption(MoveType::CHI,{ Tile::tileFromSpecs(hand.getHandTile(foundId[i]).getSuit(),5,0),hand.getHandTile(foundId[i + 1]) }));
				}
				else if (hand.getHandTile(foundId[i + 1]).getValue() == 5) {
					options.push_back(
						MoveOption(MoveType::CHI, { hand.getHandTile(foundId[i]),Tile::tileFromSpecs(hand.getHandTile(foundId[i + 1]).getSuit(),5,0) }));
				}
			}

		}
	}

	return flag;
}

void Player::executeChi(const MoveOption& chosenOption, Discards& discards, const Wind& otherWind)
{
	hand.createTriplet<Chi>(discards, chosenOption.tiles[0],chosenOption.tiles[1], relativeMarker(otherWind));
}

bool Player::daiminkanOptions(const Tile& discard)
{
	int counter = 0;
	for (int i = 0; i < hand.getHandTilesNum(); i++) {
		if (Tile::isEqual(hand.getHandTile(i), discard))
		{
			counter++;
		}
	}
	if (counter == 3) {
		Tile t1 = Tile::getDiffCopy(discard, 1);
		Tile t2 = Tile::getDiffCopy(discard, 2);
		Tile t3 = Tile::getDiffCopy(discard, 3);
		options.push_back(MoveOption(MoveType::DAIMINKAN, { t1,t2,t3 }));
		return true;
	}
	else {
		return false;
	}
}

void Player::executeDaiminkan(const MoveOption& chosenOption, Discards& discards, const Wind& otherWind)
{
	hand.createDaiminkan(discards, chosenOption.tiles[0], chosenOption.tiles[1], chosenOption.tiles[2], relativeMarker(otherWind));
}

void Player::initHand(Hand&& inputHand)
{
	if (hand.isEmpty() != true) {
		throw handAlreadyInitiated();
	}
	hand = std::move(inputHand);
	hand.sortHand();
}



RelativePosition Player::getRelativePosition( const Wind& other) const
{
	RelativePosition res = static_cast<RelativePosition>((static_cast<int>(wind)
		- static_cast<int>(other) + Constants::PLAYERS_NUM) % Constants::PLAYERS_NUM);
	return res;
}

void Player::updateOptionsDiscard(const Tile& tile, const Wind& otherWind)
{
	options.clear();
	ponOptions(tile);
	chiOptions(tile,otherWind);
	daiminkanOptions(tile);
}

void Player::resetOptions()
{
	options.clear();
}

const std::vector<MoveOption>& Player::getOptions() const
{
	return options;
}

