#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

/**
 * @brief wall class stores data of tiles yet to be drawn by the players.
 * wall tiles data doesn't change ownership after being drawn, only copied.
 * wall has tail and head indices to mark the undiscarded tiles.
 */
class Wall {

public:
	//----------------------------------------
	//nested classes
	//----------------------------------------

	//exceptions
	class emptyWall : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an empty wall";
		}
	};
	class invalidDora : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an unrevealed dora";
		}
	};
	class invalidUraDora : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make operation on an unrevealed uraDora";
		}
	};

	//constIterator class:
	class ConstIterator {
	private:
		const Tile* tile;
	public:
		ConstIterator(const Tile* tile);
		const Tile& operator*() const;
		ConstIterator& operator++();
		bool operator!=(const ConstIterator& other) const;
	};



	ConstIterator begin() const;
	ConstIterator end() const;

	//--------------------------------------------------------


	Wall();
	
	/**
	 * @return the number of tiles yet to be drawn in the wall.
	 */
	int tilesLeft() const;
	//calculates tiles left based off of head and tail

	/**
	 * @brief draw a tile from the wall, decrease tail index.
	 * @return the drawn tile
	 */
	const Tile& draw();

	/**
	 * @return number of kans made in the game 
	 */
	int addedKanCount() const;

	/**
	 * @brief draw the kan draw tile from dead wall.
	 * replace the drawn tile with another one from the wall.
	 * increase dora indicators.
	 * @return the kan draw tile.
	 */
	Tile kanDraw();

	/**
	 * @brief naively adds dora indicators
	 */
	void addDora();

	/**
	 * @brief read only access to revealed dora tiles
	 * @param index of desired dora tile index [0,doraNum - 1]
	 * @return dora tile data.
	 */
	const Tile& dora(int index) const;

	/**
	 * @brief read only access to revealed uradora tiles
	 * @param index of desired uradora tile index [0,doraNum - 1]
	 * @return uradora tile data.
	 */
	const Tile& uraDora(int index) const;
	








	

private:
	/**	 * @brief normal wall data	 */
	std::vector<Tile> wall;

	/**	 * @brief dead wall data	 */
	std::vector<Tile> deadWall;

	/**	 * @brief amount of doras currently active ingame	 */
	int doraNum;

	/**	 * @brief index of the current frontmost legal drawing tile  */
	int head;
	/**	 * @brief index of the current backmost legal drawing tile  */
	int tail;

	//constants:
	static constexpr int KAN_DRAW_ID = 0;
	static constexpr int DORA_ID = 4;
	static constexpr int  URA_ID = 9;
	static constexpr int DEAD_WALL_SIZE = 14;

};