#include "Tile.h"
#include <stdexcept>

Tile::Tile(Suit suit, int value, int copy) : suit(suit), value(value), akadora(false) {
	if (value > 9 || value < 1) {
		throw wrongValue();
	}
	if (suit == Suit::HONOR && value > 7) {
		throw wrongValueHonor();
	}
	if (suit != Suit::HONOR && copy == AKADORA_COPY && value == AKADORA_VALUE) {
		akadora = true;
	}
	id = ((static_cast<int>(suit) * TILES_IN_SUIT * COPIES) + ((value - 1) * COPIES) + copy);
}

Tile::Tile(HonorType type, int copy) : Tile(Suit::HONOR, static_cast<int>(type), copy) {}

std::string Tile::getHonorName() const {
	if (suit != Suit::HONOR) {
		throw std::invalid_argument("Input tile is not an honor tile");
	}
	switch (this->value) {
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
	switch (this->suit) {
	case Suit::MAN:
		suitName = "man";
		valueName = std::to_string(value);
		break;
	case Suit::PIN:
		suitName = "pin";
		valueName = std::to_string(value);
		break;
	case Suit::SOU:
		suitName = "sou";
		valueName = std::to_string(value);
		break;
	case Suit::HONOR:
		valueName = getHonorName();
		if (value <= DRAGONS_NUM) {
			suitName = "dragon";
		}
		else {
			suitName = "wind";
		}
		break;
	}
	std::string result = valueName + " " + suitName;
	if (akadora == true) {
		return "Red " + result;
	}
	else {
		return result;
	}
}

Suit Tile::getSuit() const {
	return suit;
}

int Tile::getValue() const {
	return value;
}

bool Tile::isAkadora() const {
	return akadora;
}

int Tile::getId() const {
	return id;
}


