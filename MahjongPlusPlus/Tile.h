#pragma once
#include <string>
#include <stdexcept>


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
	Suit suit;
	int value;
	bool akadora;
	int id;
	
	//private constants:

	static constexpr int TILES_IN_SUIT = 9;
	static constexpr int COPIES = 4;
	static constexpr int SUIT_NUM = 4;

	//dictates identity of the akadora tile
	static constexpr int AKADORA_COPY = 0;
	static constexpr int AKADORA_VALUE = 5;

	static constexpr int DRAGONS_NUM = 3;
	static constexpr int WINDS_NUM = 4;

public:
	//public constants:
	static constexpr int TOTAL_TILES_NUM = 136;


	//c'tors
	Tile() = default;
	Tile(Suit suit, int vlaue, int copy);
	Tile(HonorType, int copy);

	//getters:

	std::string getHonorName() const;

	std::string getName() const;

	Suit getSuit() const;

	int getValue() const;

	bool isAkadora() const;

	int getId() const;




	//exceptions
	class wrongValue : public std::exception {
	public:
		const char* what() const noexcept override {
			return "passed a tile value that is not between 1 to 9";
		}
	};
	class wrongValueHonor : public std::exception {
	public:
		const char* what() const noexcept override {
			return "passed an honor tile value that is not between 1 to 7";
		}
	};
};