#include "Core/MoveOption.h"
#include "Core/Tile.h"
#include "Core/GameTypes.h"
#include <iostream>

MoveOption::MoveOption(MoveType type, std::initializer_list<Tile> inputTiles) : type(type), tiles{} {

	if (inputTiles.size() != typeToSize(type)) {
		for (const auto& tile : tiles) {
		}
		throw unmatchingSize();
		
	}
	int i = 0;
	for (const Tile& tile : inputTiles) {
		tiles[i] = tile;
		i++;
	}
}

MoveOption::MoveOption(MoveType moveType) : tiles{}
{

	if (moveType == MoveType::WAITING) {
		type = MoveType::WAITING;
	}
	else if (moveType == MoveType::SKIP) {
		type = MoveType::SKIP;
	}
	else {
		throw unmatchingOption();
	}
}

MoveOption::MoveOption(): tiles{}
{
	type = MoveType::WAITING;
}

int MoveOption::typeToSize(MoveType type){
	switch (type) {
	case MoveType::WAITING:
		return 0;
		break;
	case MoveType::SKIP:
		return 0;
		break;
	case MoveType::PON:
		return 2;
		break;
	case MoveType::CHI:
		return 2;
		break;
	case MoveType::ANKAN:
		return 4;
		break;
	case MoveType::DAIMINKAN:
		return 3;
		break;
	case MoveType::SHOUMINKAN:
		return 1;
		break;
	case MoveType::RIICHI:
		return 1;
		break;
	case MoveType::TSUMO:
		return 1;
		break;
	}

}


int MoveOption::size() const{
	return typeToSize(type);
}

const MoveType& MoveOption::getType() const
{
	return type;
}

std::string MoveOption::optionToString() const
{
	std::string type = MoveOption::TYPE_NAMES[static_cast<int>(getType())];
	std::string res = "Type: " + type + " Tiles : ";
	for (int i = 0; i < size(); i++) {
		res += (tiles[i].getName() + " ");
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, const MoveOption& option)
{
	os << "Type:" << MoveOption::TYPE_NAMES[static_cast<int>(option.getType())] << " Tiles: ";
	for (int i = 0; i < option.size(); i++) {
		os << option.tiles[i] << " ";
	}
	os << std::endl;
	return os;
}
