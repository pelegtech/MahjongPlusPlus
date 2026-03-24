#pragma once
#include "Core/tile.h"
#include "Core/Discards.h"
#include "Core/GameTypes.h"
#include "Core/Triplet.h"
#include <memory>
#include <vector>
#include <exception>
#include <string>
#include <array>



class Meld;

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

	class illegalHandSize : public std::exception {
	public:
		const char* what() const noexcept override {
			return "hand holds illegal amount of tiles";
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

	class notHoldingDrawnTile : public std::exception {
	public:
		const char* what() const noexcept override {
			return "tried to make operation on drawn tile while not holding any";
		}
	};


	//public constants -----------------------------------------------------
	static constexpr int MAX_HAND_SIZE = 14;
	static constexpr int MAX_HAND_TILES_NUM = 13;
	static constexpr int MAX_MELDS_NUM = 4;

	//c'tors ---------------------------------------------------------------

	//because of the unique_ptrs in melds vector
	Hand(const Hand&) = delete;
	Hand& operator=(const Hand&) = delete;

	//because vectors can handle themselves
	Hand(Hand&&) noexcept = default;
	Hand& operator=(Hand&&) noexcept = default;


	/** @brief creates an empty hand with 0 tiles or melds.*/
	Hand();

	/**
	 * @brief create a hand using a pre existing 13 tiles array. (only sets the hand tiles array, rest are defaulted).
	 * @param handTiles an array with 13 tiles in it.
	 */
	Hand(std::array<Tile, MAX_HAND_TILES_NUM> handTiles);

	/** @brief creates a hand from existing vectors.
	* @param tiles contains (0-14) tiles. 
	* @param melds acontains (0-4) melds (pon,kan,chi).
	*/
	Hand(std::vector<Tile> tiles, std::vector<std::unique_ptr<Meld>> melds);

	//operators--------------------------------------------------------------

	

	/** @brief  prints the tiles in the hand for debug purposes*/
	friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

	//same thing but to a string
	std::string handToString() const;

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
		auto first = handTiles.begin();
		auto last = handTiles.begin() + handTilesNum;
		auto it1 = std::lower_bound(first, last, t1);
		auto it2 = std::lower_bound(first, last, t2);

		if (it1 == last || it1->getId() != t1.getId() ||
			 it2 == last || it2->getId() != t2.getId()) {
			throw tileNotFound();
		}

		Tile external = discardsPile.removeTile();
		melds.push_back(std::make_unique<T>(external,t1,t2, marker));
		
		auto rightIt = std::max(it1, it2);
		auto leftIt = std::min(it1, it2);

		std::move(rightIt + 1, last, rightIt);
		std::move(leftIt + 1, last - 1, leftIt);

		handTilesNum -= 2;
	}

	/** @brief create ankan from 4 tiles in the hand.
	* @param tile - hand tile to make kan with, MUST be the copy with the lowest tile id.
	*/
	void createAnkanDrawn();

	//another version if the kan is made from a hand tile.
	void createAnkanHand(const Tile& tile);

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
	void createShouminkanDrawn();
	
	//another version for the case of the kan being made from a hand tile.
	void createShouminkanHand(const Tile& tile);


	//getters ------------------------------------------
	/** @returns the number of free tiles in the hand including drawn tile*/
	int freeTilesNum() const; 

	/** @returns the number of tiles counted towards a valid hand
	* @note kan counts as 3 tiles.
	*/
	int legalHandSize() const;

	/** @returns the combined number of free tiles and meld tiles.
	* @note kan counts as 4 tiles.
	*/
	int realHandSize() const; 

	/**
	 * @return read only acces to drawn tile field. 
	 */
	const Tile& getDrawnTile() const;

	/**
	 * @brief checks if drawn tile field has a default tile (id = - 1) or an actual tile (id != -1).
	 * @return true if id != -1.
	 */
	bool isHoldingDrawnTile() const;

	/**
	 * @param index [0,handTilesNum - 1]
	 * @return read only access to hand tiles (the free tiles that aren't the drawn tile or a meld tile).
	 */
	const Tile& getHandTile(int index) const;

	/**
	 * @return read only access to hand tiles array.
	 */
	const std::array<Tile, MAX_HAND_TILES_NUM>& getHandTiles() const;

	/**
	 * @return the number of tiles in the hand tiles array that aren't set to a default tile (id = -1).
	 */
	int getHandTilesNum() const;

	/**
	 * @return read only access to a meld. 
	 */
	const std::vector<std::unique_ptr<Meld>>& getMelds() const;

	/**
	 * @brief add a tile directly to the handTiles array in a sorted manner (using binary search).
	 * @param tile to be added.
	 */
	void addTile(const Tile& tile);

	/**
	 * @brief checks if a hand's handTiles array is all set to default (id = -1) meaning the hand tiles array is "empty".
	 * also checks if the melds vector is empty.
	 * @return true if both are empty.
	 */
	bool isEmpty() const;

	/**
	 * @brief inneficiently (O(N)) checks if a tile exists in the hand tiles array.
	 * @param tile to be checked.
	 * @return true if exists in the hand tiles array.
	 */
	bool isTileInHandTiles(const Tile& tile) const;


private:

	/** @brief includes the free tiles, those can be discarded and be used for a meld*/
	std::array<Tile, MAX_HAND_TILES_NUM> handTiles;

	/** @brief includes the melds, those are locked and cannot be discarded or changed*/
	std::vector<std::unique_ptr<Meld>> melds;

	/**
	 * @brief the amount of hand tiles (not inclduing drawn tile or meld tiles) that are not set to default (id = -1),
	 * meaning the tiles the hand is actually containing. 
	 */
	int handTilesNum;

	/**	 * @brief the tile the hand is "holding" at the current moment. 	 */
	Tile drawnTile;
	
};
