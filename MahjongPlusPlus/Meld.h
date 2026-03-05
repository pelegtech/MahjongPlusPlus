#pragma once
#include <array>
#include "Tile.h"
#include <stdexcept>
#include <string>
#include "GameTypes.h"


/**
* @class Meld
* @brief base abstract class representing a closed set of tiles in the forms:
* chi,pon,kan. a meld is formed by taking another player's discards. tiles formed
* into a meld cannot be turned back to free tiles.
*/
class Meld {

public:
	//consts -----------------------------------
	static constexpr int KAN_SIZE = 4;
	static constexpr int TRIPLET_SIZE = 3;
	/**
	* @brief constructs meld with a marker indicating the the player who discarded the tile.
	*/
	Meld(TileMarker marker); 
	/**
	* @brief returns number of tiles in meld.
	* @return 3 for chi or pon, 4 for kan.
	*/
	virtual int size() const = 0;
	virtual ~Meld()  = default;

	/**
	* @brief read only access to a tile in the meld.
	* @param index position of tile in meld (0 - 3/4)
	*/
	virtual const Tile& operator[](int index) const = 0;

	/**@return marker indicates the player who discarded the tile. */
	TileMarker getTileMarker() const;

	/**@return string with tile contents of the meld for debugging. */
	virtual std::string getContents() const = 0;

	/**@return prints the string from getContents. */
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);

private:
	TileMarker marker;
};


