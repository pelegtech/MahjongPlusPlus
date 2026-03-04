#pragma once
#include <array>
#include "Tile.h"
#include <stdexcept>
#include <string>
#include "GameTypes.h"



class Meld {
private:
	TileMarker marker;
public:
	Meld(TileMarker marker); 
	virtual int size() const = 0;
	virtual ~Meld()  = default;
	virtual const Tile& operator[](int index) const = 0;
	TileMarker getTileMarker() const;
	static constexpr int KAN_SIZE = 4;
	static constexpr int TRIPLET_SIZE = 3;
	virtual std::string getContents() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
};


