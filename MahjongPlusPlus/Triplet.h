#pragma once
#include "Meld.h"

/**
 * @brief abstract class in charge of pon and chi.
 * contains data of melds made up of 3 tiles.
 */
class Triplet : public Meld {
private:
	std::array<Tile, 3> tiles;
public:
	/**
	 * @brief c'tpr
	 * @param externalTile tile discarded from another player.
	 * @param tile2 tile3 tiles from the hand.
	 * @param marker marks the player who discarded the external tile. 
	 */
	Triplet(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);

	/**	 * @return size of pon / chi (3) 	 */
	int size() const override;

	/**
	 * @brief read only access to tiles inside the meld.
	 * @param index [0,2]
	 * @return requeted tile
	 */
	const Tile& operator[](int index) const override;

	virtual ~Triplet() = default;
};

/**
 * @brief a meld made of 2 hand tiles and one external tile
 * (all share same suit and value)
 */
class Pon : public Triplet {
public:

	//exceptions:
	class notPon : public std::exception {
	public:
		const char* what() const noexcept override {
			return "pon must only contain three identical tiles";
		}
	};

	/**
	 * @brief c'tor
	 * @param externalTile tile from another player's discards.
	 * @param tile2 tile3 the hand tiles
	 * @param marker marks the player who discarded the external tile. 
	 */
	Pon(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);

	~Pon() override = default;

	/**
	 * @brief checks if given tiles make for a legal pon 
	 * (all share same suit and value)
	 * @param t1 t2 t3 tiles to be compared
	 * @return true if legal pon false otherwise.
	 */
	static bool isPon(const Tile& t1, const Tile& t2, const Tile& t3);

	/**	 * @return string contianing pon tiles fata for debug purposes.	 */
	virtual std::string getContents() const override;



};

/**
 * @brief meld of 3 tiles two from hand one external
 * make a sequence (e.g. 1s,2s,3s) all from same suit.
 */
class Chi : public Triplet {
public:
	//exceptions:
	class notChi : public std::exception {
	public:
		const char* what() const noexcept override {
			return "chi must  contain a sequence of three consecutive tiles";
		}
	};

	/**
	 * @brief c'tor
	 * @param externalTile tile from another player's discards.
	 * @param tile2 tile3 tiles from the hand .
	 * @param marker marks the player who discarded the external tile.
	 */
	Chi(const Tile& externalTile, const Tile& tile2, const Tile& tile3, TileMarker marker);

	~Chi() override = default;
	
	/**
	 * @brief checks if given tiles make for a legal chi
	 * (tiles make for a sequence of the same suit)
	 * @param t1 t2 t3 tiles to be compared
	 * @return true if legal chi false otherwise.
	 */
	static bool isChi(const Tile& t1, const Tile& t2, const Tile& t3);

	/**	 * @return string contianing pon tiles fata for debug purposes.	 */
	virtual std::string getContents() const override;


	
};
