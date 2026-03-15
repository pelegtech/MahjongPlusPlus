#include "Core/MoveOption.h"
#include "Core/Tile.h"
#include "Core/GameTypes.h"


MoveOption::MoveOption(MoveType type, std::initializer_list<Tile> inputTiles) : type(type) {
	if (tiles.size() != typeToSize(type)) {
		throw unmatchingSize();
	}
	int i = 0;
	for (const Tile& tile : inputTiles) {
		tiles[i] = tile;
		i++;
	}
}

int MoveOption::typeToSize(MoveType type){
	switch (type) {
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