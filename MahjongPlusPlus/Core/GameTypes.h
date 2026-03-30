#pragma once
enum class Suit {
	MAN,
	PIN,
	SOU,
	HONOR,
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
	NORTH,
};

enum class TileMarker {
	SELF,
	LEFT,
	MIDDLE,
	RIGHT,
};

enum class MoveType {
	WAITING,
	SKIP,
	PON,
	CHI,
	ANKAN,
	DAIMINKAN,
	SHOUMINKAN,
	RIICHI,
	TSUMO,
	RON,
	COUNT,
};

enum class MeldType {
	PON,
	CHI,
	ANKAN,
	DAIMINKAN,
	SHOUMINKAN,
};

enum class GameState {
	INIT_ROUND,
	TURN_START,
	TURN_END,
	DRAW,
	KAN_DRAW,
	WAITING_FOR_TURN_ACTION,
	EVALUATE_DISCARD,
	WAITING_FOR_DISCARD_DECISIONS,
	RESOLVE_CALLS,
	ROUND_END,
	GAME_OVER,
};

enum class RelativePosition {
	SELF,
	LEFT,
	TOP,
	RIGHT,
};

enum class UIState {
	HIDDEN,
	SELECTING_TYPE,
	SELECTING_MELD,
};

namespace Constants {

	constexpr int PLAYERS_NUM = 4;
	constexpr int SCREEN_WIDTH = 1920;
	constexpr int SCREEN_HEIGHT = 1080;
	constexpr int TOTAL_TILES_NUM = 136;
	constexpr int TILE_KINDS = 34;
	constexpr int TILE_COPIES = 4;

}

enum class handType {
	STANDARD,
	SEVEN_PAIRS,
	THIRTEEN_ORPHANS,
};

enum class BlockType {
	UNSET,
	OPEN_SEQUENCE,
	CLOSED_SEQUENCE,
	OPEN_TRIPLET,
	CLOSED_TRIPLET,
	OPEN_KAN,
	CLOSED_KAN,
};