#pragma once
#include "Core/GameTypes.h"
#include <string>
#include <stdexcept>
#include <iostream>


/**
 * @class Tile
 * @brief Represents a mahjong tile out of the 136 tiles in a standard riichi set.
 * each tile is uniquely represented by an id in the range [0,135] which dictates
 * its suit, value, copy number and whether it's an "akadora" tile. 
 */
class Tile {

public:

	//exceptions ------------------------------------------
	/**@brief thrown in case of a tile id outside the range of [0,135]*/
	class InvalidTileID : public std::exception {
	public:
		const char* what() const noexcept override {
			return "passed a tile id higher than 135 or lower than 0";
		}
	};

	/**@brief thrown in case of a tile value outside the range of [1,9]*/
	class InvalidTileValue : public std::exception {
	public:
		const char* what() const noexcept override {
			return "passed a tile value higher than 9 or lower than 1";
		}
	};

	/**@brief thrown in case of an honor  tile with value higher than 7*/
	class InvalidTileValueHonor : public std::exception {
	public:
		const char* what() const noexcept override {
			return "passed an honor value higher than 7";
		}
	};

	class EmptyTile: public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an empty tile (id = -1)";
		}
	};


	//public constants ------------------------------------------
	static constexpr int TOTAL_TILES_NUM = 136;

	//dictates identity of the akadora tile:
	static constexpr int AKA_MAN = 16;
	static constexpr int AKA_PIN = 52;
	static constexpr int AKA_SOU = 88;
	static constexpr int EMPTY_TILE_ID = -1;

	//c'tors ------------------------------------------
	Tile();

	/** @brief creates a tile based on id alone.
	* @param id Integer in the range [0,135].
	*/
	Tile(int id);

	
	//oprators ------------------------------------------
	/**
	* @brief Compares tiles by their id alone.
	* @param The tile you want to compare this tile to.
	* @return true if this tile's id is lower than the other's
	*/
	bool operator<(const Tile& other) const;

	bool operator==(const Tile& other) const;

	/**@brief prints tile name and id for debug purposes*/
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);

	//other methods ------------------------------------------

	//create tile from parameters:
	/**
	* @brief creates a tile based off it's characteristics.
	* @param suit (Man,Pin,Sou,Honor)
	* @param value suit tile value in the range [0,9] honors in range [0,7].
	* @param copy index in the range [0,3] since each tile has 4 copies.
	* @return a tile with given values.
	*/
	static Tile tileFromSpecs(Suit suit, int value, int copy);

	/**
	* @brief creates an honor tile based off it's name.
	* @param type the honor tile name(RED_DRAGON, EAST_WIND etc...).
	* @param copy index in the range [0,3] since each tile has 4 copies.
	* @return a tile with given values.
	*/
	static Tile honorTileFromSpecs(HonorType type, int copy);

	/**
	* @brief Compares tiles by their suit and value ignoring unique id.
	* @param tile1 first tile to compare.
	* @param tile2 second tile to compare.
	* @return returns ture if their suit and value are equal (copies of the samme tile).
	*/
	static bool isEqual(const Tile& tile1, const Tile& tile2);


	//getters ---------------------------------------
	int getId() const;

	/** @return returns suit calculated by the unique tile id.*/
	Suit getSuit() const;

	/** @return returns tile value calculated by the unique tile id.*/
	int getValue() const;
	
	/** @return a sting containg name of a tile (e.g. 1pin, red dragon etc...) */
	std::string getName() const;

	/**
	* @brief checks if tile is an akadora.
	* @return true if tile is of specific dictated akadora id.
	*/
	bool isAkadora() const;
	
	
private:
	
	//private constants-----------------------------------
	static constexpr int DRAGONS_NUM = 3;
	static constexpr int WINDS_NUM = 4;
	static constexpr int VALUES_IN_SUIT = 9;
	static constexpr int TILES_IN_SUIT = 36;
	static constexpr int COPIES = 4;
	static constexpr int SUIT_NUM = 4;
	static constexpr int HONORS_NUM = 7;

	

	//private methods---------------------------------------
	/**
	* @brief helper function for public method getName
	* @return part of the honor's name (e.g. Red, South etc...)
	*/
	std::string getHonorName() const;
	

	//private fields ---------------------------
	/** @brief unique tile identifier dictates entire state of the tile */
	int id; 


};