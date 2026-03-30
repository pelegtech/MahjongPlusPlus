#pragma once
#include <array>
#include "GameTypes.h"
#include "Tile.h"
class Tile;

class Block {
private:
public:
	static bool isTriplet(const Tile& t1, const Tile& t2, const Tile& t3);
	static bool isSequence(const Tile& t1, const Tile& t2, const Tile& t3);
	virtual ~Block() = default;
};

class BlockTriplet: public Block{
private:
	BlockType type;
	std::array<Tile, 3> tiles;
	Tile extraTile; 
public:
	BlockTriplet();
	BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, BlockType type);
	BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, BlockType type);

};

class BlockPair: public Block {
	private:
	std::pair<Tile, Tile> tiles;
public:
	BlockPair() = default;
	BlockPair(const Tile& t1, const Tile& t2);
};

