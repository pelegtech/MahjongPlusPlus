#pragma once
#include <array>

class Tile;

class Block {
public:
	virtual ~Block() = default;
};

class BlockTriplet: public {
private:
	std::array<Tile, 3> tiles;
	Tile extraTile; 
public:
	BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3);
	BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);

};

class BlockPair {
private:
	std::pair<Tile, Tile> tiles;
public:
	BlockPair(const Tile& t1, const Tile& t2);
};

