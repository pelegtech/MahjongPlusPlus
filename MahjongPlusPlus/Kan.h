#pragma once
#include "Meld.h"
#include "Triplet.h"

/**
 * @brief kan abstract class in charge of all kan-type data structures.
 * kan holds data of a meld consisting of four tiles.
 */
class Kan : public Meld {

public:
	//exception class
	class notKan : public std::exception {
		const char* what() const noexcept override {
			return "kan must contain four identical tiles";
		}
	};

	/**
	 * @brief c'tor
	 * @param t1 t2 t3 t4 tiles to be stored in the kan meld.
	 * @param marker marks the player that owns the discarded tile.
	 */
	Kan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4, TileMarker marker);

	/**
	 * @return kan size 4
	 */
	int size() const override;

	/**
	 * @brief read only access to the kan tiles
	 * @param index [0,3]
	 * @return requested tile
	 */
	const Tile& operator[](int index) const override;

	virtual ~Kan() = default;

	/**
	 * @brief checks if given tiles can make a legal kan (all are equal in value and suit)
	 * @param t1 t2 t3 t4 tiles to be compared
	 * @return true if legal kan, false if not.
	 */
	static bool isKan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);


	

private:
	/**	 * @brief kan tiles data	 */
	std::array<Tile, 4> tiles;
};


/**
 * @brief ankan is a closed kan made entirely from hand tiles.
 */
class Ankan : public Kan {
public:

	Ankan(const Tile& t1, const Tile& t2, const Tile& t3, const Tile& t4);

	/**	 * @return string containing kan tiles data for debug purposes.	 */
	virtual std::string getContents() const override;

	~Ankan() = default;
};

/**
 * @brief daiminkan is an open kan made from 3 tiles inside the hand and one external tile.
 */
class Daiminkan : public Kan {
public:
	/**
	 * @brief c'tor
	 * @param externalTile tile from outside the hand
	 * @param tile2 tile3 tile 4 tiles from inside the hand
	 * @param marker marks the player who discarded the external tile
	 */
	Daiminkan(const Tile& externalTile, const Tile& tile2,
	const Tile& tile3, const Tile& tile4, TileMarker marker);

	/**	 * @return string containing kan tiles data for debug purposes.	 */
	virtual std::string getContents() const override;

	~Daiminkan() = default;
};


/**
 * @brief kan made from a previously created pon and one drawn tile.
 */
class Shouminkan : public Kan {
public:
	/**
	 * @brief c'tor
	 * @param drawnTile tile drawn from the wall
	 * @param pon previously created pon from the hand
	 */
	Shouminkan(const Tile& drawnTile, std::unique_ptr<Pon> pon);

	/**	 * @return string containing kan tiles data for debug purposes.	 */
	virtual std::string getContents() const override;

	~Shouminkan() = default;
};