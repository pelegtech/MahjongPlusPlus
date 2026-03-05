#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

class Wall {
private:
	std::vector<Tile> wall;
	std::vector<Tile> deadWall;
	int doraNum;
	int head;
	int tail;

	//constants:
	static constexpr int KAN_DRAW_ID = 0;
	static constexpr int DORA_ID = 4;
	static constexpr int  URA_ID = 9;
	static constexpr int DEAD_WALL_SIZE = 14;

public:

	
	Wall();
	//initializes wall and dead wall with random tiles

	//hopefully all of the methods below are O(1) time complexity

	int tilesLeft() const;
	//calculates tiles left based off of head and tail

	Tile draw();

	int addedKanCount() const;
	//returns the amount of additional kans made

	Tile kanDraw();

	void addDora();
	//advances doraNum

	const Tile& dora(int index) const;
	//read only access to dora tiles by index [0,doraNum - 1]

	const Tile& uraDora(int index) const;
	//read only access to ura dora tiles by index [0,doraNum - 1]
	

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






	//exceptions:
	class emptyWall : public std::exception{
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


};