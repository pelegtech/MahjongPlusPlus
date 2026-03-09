#pragma once
#include "tile.h"
#include <vector>
#include <memory>
#include "Discards.h"
#include <stdexcept>
#include "GameTypes.h"
class Meld;
class Player;

/**
 * @class Hand
 * @brief represent the collection of tiles that makes a hand. 
 * this class seperates the hand into two distinct components:
 * 1. The free tiles currently held by the player.
 * 2. The locked melds, tiles that were made into chi, pon or kan. 
 * these tiles cannot be discarded.
 * this class handles the logistics of a hand such as creating a meld, 
 * drawing or discarding a tile.
 */
class Hand {
public:
	//exceptions -------------------------------------

	/**@brief thrown in case of making an illegal operation on a full hand*/
	class handIsFull : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make this operation on a full hand";
		}
	};

	/**@brief thrown in case of making an illegal operation on an empty hand*/
	class handIsEmpty : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make this operation on an empty hand";
		}
	};

	/**@brief thrown in case of trying to access a tile out of hand bounds*/
	class illegalAcess : public std::exception {
	public:
		const char* what() const noexcept override {
			return "tried to access an illegal hand tile location";
		}
	};

	class tileNotFound : public std::exception {
	public:
		const char* what() const noexcept override {
			return "tried to make a meld with a tile that is not found in the hand";
		}
	};

	class meldNotFound : public std::exception {
	public:
		const char* what() const noexcept override {
			return "tried to make a shouminkan with a meld that is not found in the hand";
		}
	};


	//public constants -----------------------------------------------------
	static constexpr int MAX_HAND_SIZE = 14;

	//c'tors ---------------------------------------------------------------

	/** @brief creates an empty hand with 0 tiles or melds.*/
	Hand() = default;

	/** @brief creates a hand from existing vectors.
	* @param tiles contains (0-14) tiles. 
	* @param melds acontains (0-4) melds (pon,kan,chi).
	*/
	Hand(std::vector<Tile> tiles, std::vector<std::unique_ptr<Meld>> melds);

	//operators--------------------------------------------------------------

	/** @brief access the hand tiles. 
	* @param index  - order of tiles in hand: 1. free tiles, 2. drawn tile, 3.meld tiles
	* @return read only access to tile
	*/
	const Tile& operator[](int index) const; 

	/** @brief  prints the tiles in the hand for debug purposes*/
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);


	//other methods -------------------------------------------------------

	/** @brief sort hand by tile index */
	void sortHand();


	/** @brief adds a tile to the end of the free tiles vector
	* @param tile to be drawn (from wall or dead wall)
	* @note this method leaves the hand unsorted
	*/
	void drawTile(const Tile& tile);

	/** @brie discards drawn (last) tile into given discards pile 
	* @param discards - (usually the players discards pile). 
	*/
	void discardDrawnTile(Discards& discards);
	

	/** @brief discards a tile by index.
	* @param discards - (usually the player's).
	* @param index - must be in range of the hand's free tiles
	*/
	void discardHandTile(Discards& discards, int index);


	/** @brief inserts drawn (last) tile into the hand. uses binary search to sort it in.
	* @note must be used on a sorted hand (excluding last tile).
	*/
	void addDrawnTile();


	
	/** @brief create a chi or pon from free tiles, add it to melds vector.
	* @param discards - belongs to the player who discarded the called tile.
	* @param t1, t2 hand tiles matching the discarded tile.
	* @param marker - indicates the player who discarded the called tile.
	*/
	template <class T>
	void createTriplet(Discards& discardsPile,
		const Tile& t1,
		const Tile& t2, TileMarker marker) {
		std::vector<Tile>::iterator it1 = std::lower_bound(tiles.begin(), tiles.end(), t1);
		std::vector<Tile>::iterator it2 = std::lower_bound(tiles.begin(), tiles.end(), t2);
		if (it1 == tiles.end() || it1->getId() != t1.getId() ||
			 it2 == tiles.end() || it2->getId() != t2.getId()) {
			throw tileNotFound();
		}
		Tile external = discardsPile.removeTile();
		melds.push_back(std::make_unique<T>(external,
			std::move(*it1), std::move(*it2), marker));
		if (it1 < it2) {
			tiles.erase(it2);
			tiles.erase(it1);
		}
		else {
			tiles.erase(it1);
			tiles.erase(it2);
		}
	}

	/** @brief create ankan from 4 tiles in the hand.
	* @param tile - hand tile to make kan with, MUST be the copy with the lowest tile id.
	*/
	void createAnkan(const Tile& tile);

	/** @brief Create a Daiminkan (open kan) using a discarded tile.
	* @param discardsPile - the pile from which the discarded tile belongs to.
	* @param t1,t2,t3 shares the same value and suit to the discarded tile.
	* @param marker indicates the player who discarded the called tile.
	*/
	void createDaiminkan(Discards& discardsPile,
		const Tile& t1, const Tile& t2, const Tile& t3, TileMarker marker);
		
	/** @brief Create a shouminkan (added kan) from a tile and a meld in the hand.
	* @param tile - the added tile, from the hand.
	* @param meldIndex index of the pon in the melds vector.
	*/
	void createShouminkan(const Tile& tile, int meldIndex);


	//getters ------------------------------------------
	/** @returns the number of free tiles in the hand*/
	int freeTilesNum() const; 

	/** @returns the number of tiles counted towards a valid hand
	* @note kan counts as 3 tiles.
	*/
	int legalHandSize() const;

	/** @returns the combined number of free tiles and meld tiles.
	* @note kan counts as 4 tiles.
	*/
	int realHandSize() const; //counts kan as 4 tiles

	/** returns the last tile in the free tiles, usually that's the drawn tile*/
	const Tile& lastTile() const;

	const std::vector<std::unique_ptr<Meld>>& getMelds() const;

private:
	/** @brief includes the free tiles, those can be discarded and be used for a meld*/
	std::vector<Tile> tiles;
	/** @brief includes the melds, those are locked and cannot be discarded or changed*/
	std::vector<std::unique_ptr<Meld>> melds;
	
};
