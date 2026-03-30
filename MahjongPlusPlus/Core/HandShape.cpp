#include "HandShape.h"


bool standardShape::getHasPair()
{
	return hasPair;
}

standardShape::standardShape() : tripletNum(0), hasPair(false)
{
}

void standardShape::popTriplet()
{
	triplets[--tripletNum] = BlockTriplet();
}

void standardShape::popPair()
{
	hasPair = false;
	pair = BlockPair();
}

void standardShape::addTriplet(const BlockTriplet& triplet)
{
	triplets[tripletNum++] = triplet;
}

void standardShape::addPair(const BlockPair& inputPair)
{
	if (hasPair) {
		throw alreadyHasPair();
	}
	hasPair = true;
	pair = inputPair;
}

sevenPairsShape::sevenPairsShape() : pairNum(0)
{
}

void sevenPairsShape::addPair(const BlockPair& pair)
{
	pairs[pairNum++] = pair;
}


