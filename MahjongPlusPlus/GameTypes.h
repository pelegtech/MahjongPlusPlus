#pragma once
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

enum class Wind {
	EAST,
	SOUTH,
	WEST,
	NORTH
};

enum class TileMarker {
	SELF,
	LEFT,
	MIDDLE,
	RIGHT
};

enum class MoveType {
	SKIP,
	PON,
	CHI,
	ANKAN,
	DAIMINKAN,
	SHOUMINKAN,
	RIICHI,
	TSUMO,
	RON
	
};

