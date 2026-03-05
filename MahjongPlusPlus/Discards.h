#pragma once
#include "Tile.h"
#include <vector>
#include <stdexcept>
#include "GameTypes.h"

class Discards {
private:
	static constexpr int UNDECIDED = -1;
	static constexpr int ROW_SIZE = 6;
	std::vector<Tile> tiles;
	int riichiTileId;
public:
	Discards();
	void addTile(const Tile& tile);
	Tile removeTile(); //returns the last tile in the pile

	//sets current last tile index to be the riichi tile
	void riichi();

	//ConstIterator 
	class ConstIterator {
	private:
		const Tile* tile;
	public:
		ConstIterator(const Tile* tile);
		const Tile& operator*() const;
		ConstIterator& operator++();
		bool operator!=(const ConstIterator& other) const;
	};

	ConstIterator begin() const;
	ConstIterator end() const;



	//exception
	class emptyDiscardsPile : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an empty discards pile";
		}
	};
};