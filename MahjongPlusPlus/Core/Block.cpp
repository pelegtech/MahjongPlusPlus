#include "Core/Block.h"
#include "Core/Tile.h"

BlockTriplet::BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, BlockType type) :type(type),
	tiles{ {t1,t2,t3} }
{

}

BlockTriplet::BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, BlockType type) :
type(type), tiles{ {t1,t2,t3} }, extraTile(t4)
{

}




BlockPair::BlockPair(const Tile& t1, const Tile& t2)
{
	tiles.first = t1;
	tiles.second = t2;
}

bool Block::isTriplet(const Tile& t1, const Tile& t2, const Tile& t3)
{
	if (Tile::isEqual(t1, t2) && Tile::isEqual(t1, t3)) {
		return true;
	}
	return false;
}

bool Block::isSequence(const Tile& t1, const Tile& t2, const Tile& t3)
{
	if (t1.getSuit() == t2.getSuit() && t1.getSuit() == t3.getSuit()) {
		if (t1.getValue() + 1 == t2.getValue() && t2.getValue() + 1 == t3.getValue()) {
			return true;
		}
	}
	return false;
}

BlockTriplet::BlockTriplet(): type(BlockType::UNSET)
{
}
