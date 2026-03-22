#pragma once
#include "Core/GameTypes.h"
#include "Core/Tile.h"
#include <array>
#include <initializer_list>
#include <exception>
#include <string>
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

	MoveOption();

	/**
	 * @brief c'tor
	 * @param moveType the type of move (KAN,CHI,RON,etc...) 
	 * @param inputTiles the hand tiles that will be used to perform the action.
	 */
	MoveOption(MoveType moveType, std::initializer_list<Tile> inputTiles);

	/**
	 * @brief create a move option without any tiles. 
	 * @param moveType types supported: SKIP, WAITING.
	 */
	MoveOption(MoveType moveType);
	
	

	/**	 * @brief the maximum amount of tiles needed to be passed for any option that exists	 */
	static constexpr  int MAX_TILE_OPTIONS = 4;

	/**
	 * @brief for debug and button use. order fits move types enum order. 
	 */
	static constexpr std::array< const char*, static_cast<int>(MoveType::COUNT)> TYPE_NAMES = {
		"WAITING","SKIP","PON","CHI","ANKAN","DAIMINKAN","SHOUMINKAN","RIICHI","TSUMO","RON"
	};

	
	/**
	 * @param type of move (KAN,CHI,RONm etc...)
	 * @return the number of tiles from the hand needed to perform the action.
	 */
	static int typeToSize(MoveType type);

	/**
	 * @return the number of cells in tiles array that are used to store meaningful data. 
	 */
	int size() const;

	
	const MoveType& getType() const;

	/**
	 * @brief cout overloading for debug prposes.
	 */
	friend std::ostream& operator<<(std::ostream& os, const MoveOption& option);

	/**
	 * @brief convert an option description to a string for debug and log purposes.
	 * @return string containing tiles and move type.
	 */
	std::string optionToString() const;


	//-----------------------------------------------------------------------------
	//PUBLIC FIELDS
	//-----------------------------------------------------------------------------

	MoveType type;

	//contains the tiles that are required to make the move, but only those from the hand. 
	//for example, if a chi is to be made from 3,4,5 and 3,4 are hand tiles while 5 is external
	//this array will only contain 3 and 4. 
	std::array<Tile, MAX_TILE_OPTIONS> tiles;


};