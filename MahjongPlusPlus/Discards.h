#pragma once
#include <vector>
#include <stdexcept>
#include "GameTypes.h"

class Tile;

/** @clas Discards
*	@brief holds information about a player's discard pool
*/
class Discards {
public:

	//------------------------------------------------------------
	//nested classes 
	//------------------------------------------------------------
	//exceptions:
	class emptyDiscardsPile : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an empty discards pile";
		}
	};

	//ConstIterator :
	class ConstIterator {
	private:
		const Tile* tile;
	public:
		ConstIterator(const Tile* tile);
		const Tile& operator*() const;
		ConstIterator& operator++();
		bool operator!=(const ConstIterator& other) const;
	};

	//----------------------------------------------------------


	ConstIterator begin() const;
	ConstIterator end() const;


	/** @brief initializes riichi tile ID to unknown */
	Discards();

	/**
	 * @brief naively adds selected tile to the pile.
	 * @param tile to be added
	 */
	void addTile(const Tile& tile);

	/**
	 * @brief removes tile from pile 
	 * @return the tile removed
	 */
	Tile removeTile(); //returns the last tile in the pile

	/**
	 * @brief sets riichi tile id to the last tile on the pile
	 */
	void riichi();

	int getRiichiId() const;

	int getSize() const;




private:
	/**	 * @brief default for riichi tile id 	 */
	static constexpr int UNDECIDED = -1;
	/**	 * @brief amount of tile in each discards row	 */
	static constexpr int ROW_SIZE = 6;
	/**	 * @brief discard tiles data	 */
	std::vector<Tile> tiles;
	/**	 * @brief marks the number of the tile to mark a riichi.	 */
	int riichiTileId;

};