#pragma once
#include <vector>
#include <array>
#include "Block.h"




class HandShape {
private:
public:
	HandShape() = default;
	virtual ~HandShape() = default;
};

class standardShape : public HandShape {
private:
	std::array<BlockTriplet, 4> triplets;
	int tripletNum;
	BlockPair pair;
	bool hasPair;
public:
	class alreadyHasPair : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot add a pair to a hand that has a pair already";
		}
	};

	bool getHasPair();
	standardShape();
	void popTriplet();
	void popPair();
	void addTriplet(const BlockTriplet& triplet);
	void addPair(const BlockPair& inputPair);
};

class sevenPairsShape : public HandShape {
private:
	std::array<BlockPair, 7> pairs;
	int pairNum;
public:
	sevenPairsShape();
	void addPair(const BlockPair& pair);
};

class thirteenOrphansShape : public HandShape {
private:
	std::array < Tile, 12 > tiles;
	BlockPair pair;
public:
	thirteenOrphansShape() = default;
	void addPair(const BlockPair& pair);
	void addTile(const Tile& tile);
};