#pragma once
#include "Core/GameTypes.h"
#include "Core/Tile.h"
#include <array>
#include <initializer_list>
#include <exception>
/**
 * @brief data structure to store an option for any type of move besides discard
 *	a player can perform on his turn. this struct exist to assist displaying
 *	and executing the moves.
 */
class Tile;
struct MoveOption {
	//exceptions:
	class unmatchingSize : public std::exception {
		const char* what() const noexcept override {
			return "amount of tiles passed to the c'tor doesn't match the type";
		}
	};

	class unmatchingOption : public std::exception {
		const char* what() const noexcept override {
			return "requested execution does not match option type";
		}
	};

	/**
	 * @brief c'tor
	 * @param moveType the type of move (KAN,CHI,RON,etc...) 
	 * @param inputTiles the hand tiles that will be used to perform the action.
	 */
	MoveOption(MoveType moveType, std::initializer_list<Tile> inputTiles);

	/**	 * @brief the maximum amount of tiles needed to be passed for any option that exists	 */
	static constexpr  int MAX_TILE_OPTIONS = 4;

	
	/**
	 * @param type of move (KAN,CHI,RONm etc...)
	 * @return the number of tiles from the hand needed to perform the action.
	 */
	static int typeToSize(MoveType type);

	/**
	 * @return the number of cells in tiles array that are used to store meaningful data. 
	 */
	int size() const;


	//fields: 

	MoveType type;

	std::array<Tile, MAX_TILE_OPTIONS> tiles;
};