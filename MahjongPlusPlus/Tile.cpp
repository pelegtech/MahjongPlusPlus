#include "Tile.h"
#include <stdexcept>

Tile::Tile(int id) : id(id){
	if (id < 0 || id > 135) {
		throw invalidTileID();
	}
}

Tile Tile::tileFromSpecs(Suit suit, int value, int copy){
	if (value > 9 || value < 1) {
		throw invalidTileValue();
	}
	if (suit == Suit::HONOR && value > HONORS_NUM) {
		throw invalidTileValueHonor();
	}
	int id = ((static_cast<int>(suit) * TILES_IN_SUIT * COPIES) + ((value - 1) * COPIES) + copy);
	Tile res = Tile(id);
	return res;
}

Tile Tile::honorTileFromSpecs(HonorType type, int copy) {
	Tile res = tileFromSpecs(Suit::HONOR, static_cast<int>(type), copy);
	return res;
}

std::string Tile::getHonorName() const {
	if (getSuit() != Suit::HONOR) {
		throw std::invalid_argument("Input tile is not an honor tile");
	}
	switch (this->getValue()) {
	case static_cast<int>(HonorType::WHITE_DRAGON):
		return  "White";
	case static_cast<int>(HonorType::GREEN_DRAGON):
		return  "Green";
	case static_cast<int>(HonorType::RED_DRAGON):
		return  "Red";
	case static_cast<int>(HonorType::EAST_WIND):
		return  "East";
	case static_cast<int>(HonorType::SOUTH_WIND):
		return  "South";
	case static_cast<int>(HonorType::WEST_WIND):
		return  "West";
	case static_cast<int>(HonorType::NORTH_WIND):
		return  "North";
	}
}


std::string Tile::getName() const {
	std::string suitName;
	std::string valueName;
	switch (this->getSuit()) {
	case Suit::MAN:
		suitName = "man";
		valueName = std::to_string(getValue());
		break;
	case Suit::PIN:
		suitName = "pin";
		valueName = std::to_string(getValue());
		break;
	case Suit::SOU:
		suitName = "sou";
		valueName = std::to_string(getValue());
		break;
	case Suit::HONOR:
		valueName = getHonorName();
		if (getValue() <= DRAGONS_NUM) {
			suitName = "dragon";
		}
		else {
			suitName = "wind";
		}
		break;
	}
	std::string result = valueName + " " + suitName;
	if (isAkadora() == true) {
		return "Red " + result;
	}
	else {
		return result;
	}
}

Suit Tile::getSuit() const {
	return static_cast<Suit>(id / 36);
}

int Tile::getValue() const {
	return ((id % (TILES_IN_SUIT * COPIES)) / COPIES) + 1;
}

bool Tile::isAkadora() const {
	return (id == AKA_MAN || id == AKA_PIN || id == AKA_SOU);
}

int Tile::getId() const {
	return id;
}


//tile printing
std::ostream& operator<<(std::ostream& os, const Tile& tile) {
	os << "id= " << tile.getId() << " name: " << tile.getName() << std::endl;
	return os;
}
