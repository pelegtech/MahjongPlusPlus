#include "Core/Block.h"
#include "Core/Tile.h"

BlockTriplet::BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3) : tiles{ {t1,t2,t3} }
{

}

BlockTriplet::BlockTriplet(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4) : tiles{ {t1,t2,t3} }, extraTile(t4)
{

}




BlockPair::BlockPair(const Tile& t1, const Tile& t2)
{
	tiles.first = t1;
	tiles.second = t2;
}
