#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

enum class Suit {
	MAN,
	PIN,
	SOU,
	HONOR
};

enum class HonorType {
	WHITE_DRAGON = 1,
	GREEN_DRAGON = 2,
	RED_DRAGON = 3,
	EAST_WIND = 4,
	SOUTH_WIND = 5,
	WEST_WIND = 6,
	NORTH_WIND = 7
};


class Tile {
private:

	int id;
	
	//private constants:

	static constexpr int TILES_IN_SUIT = 9;
	static constexpr int COPIES = 4;
	static constexpr int SUIT_NUM = 4;
	static constexpr int HONORS_NUM = 7;

	//dictates identity of the akadora tile
	static constexpr int AKA_MAN = 16;
	static constexpr int AKA_PIN = 52;
	static constexpr int AKA_SOU = 88;

	static constexpr int DRAGONS_NUM = 3;
	static constexpr int WINDS_NUM = 4;

public:
	//public constants:

	static constexpr int TOTAL_TILES_NUM = 136;


	//c'tors:

	Tile() = default;
	Tile(int id);

	//create tile from parameters:

	static Tile tileFromSpecs(Suit suit, int vlaue, int copy);
	static Tile honorTileFromSpecs(HonorType, int copy);

	//getters:

	std::string getHonorName() const;
	std::string getName() const;
	Suit getSuit() const;
	int getValue() const;
	bool isAkadora() const;
	int getId() const;

	//other methods:
	static bool isEqual(const Tile& tile1, const Tile& tile2);
	

	//oprators:
	bool operator<(const Tile& other) const;

	//print
	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);

	//exceptions:
	class invalidTileID : public std::exception {
		const char* what() const noexcept override {
			return "passed a tile id higher than 135 or lower than 0";
		}
	};

	class invalidTileValue : public std::exception {
		const char* what() const noexcept override {
			return "passed a tile value higher than 9 or lower than 1";
		}
	};

	class invalidTileValueHonor : public std::exception {
		const char* what() const noexcept override {
			return "passed an honor value higher than 7";
		}
	};

	
};