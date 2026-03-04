#pragma once
#include "tile.h"
#include <string>
#include <vector>
#include <memory>
#include "Meld.h"
#include "Discards.h"
#include <stdexcept>
#include <algorithm>

class Hand {

private:
	std::vector<Tile> tiles;
	std::vector<std::unique_ptr<Meld>> melds;
	static constexpr int MAX_HAND_SIZE = 14;

public:
	int legalHandSize() const; //counts kan as 3 tiles
	int realHandSize() const; //counts kan as 4 tiles
	const Tile& operator[](int index) const; //read only


	//logic:
	//draw tiles add a tile to the tiles vector at the last position
	//add drawn tile adds it to your hand at the correct sorted position
	//discardDrawTile discards it to a given discards pile
	void drawTile(const Tile& tile);
	void addDrawnTile(); 
	void discardDrawnTile(Discards& discards);
	
	
	//creates a chi or a pon 
	template <class T>
	void createTriplet(Discards& discardsPile,
		std::vector<Tile>::iterator it1,
		std::vector<Tile>::iterator it2, TileMarker marker) {
		Tile external = discardsPile.removeTile();
		melds.push_back(std::make_unique<T>(external, 
			std::move(*it1);, std::move(*it2), marker));
		if (it1 < it2) {
			tiles.erase(it2);
			tiles.erase(it1);
		}
		else {
			tiles.erase(it1);
			tiles.erase(it2);
		}
	}
	
	void createAnkan(std::vector<Tile>::iterator it1,
		std::vector<Tile>::iterator it2, std::vector<Tile>::iterator it3,
		std::vector<Tile>::iterator it4);

	void createDaiminkan(Discards& discardsPile,
		std::vector<Tile>::iterator it1,std::vector<Tile>::iterator it2, 
		std::vector<Tile>::iterator it3, TileMarker marker);

	void createShouminkan(std::vector<Tile>::iterator it1,
		std::vector<std::unique_ptr<Meld>>::iterator it);


	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

	class handIsFull : public std::exception {
		const char* what() const override {
			return "cannot make this operation on a full hand";
		}
	};
	class handIsEmpty : public std::exception{
		const char* what() const override {
			return "cannot make this operation on an empty hand";
		}
	};


};