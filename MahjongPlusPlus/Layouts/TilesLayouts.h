#pragma once
#include "Core/GameTypes.h"
#include "raylib.h"
#include <array>
#include <vector>
#include <memory>
#include <iostream>

class Player;
class Hand;
class Meld;
class Discards;

/**
 * @brief provides dimensions and positions for 
 *	hand tiles for graphics and input classes to use uniformly.
 */
struct HandTilesLayout {

	//----------------------------------------------------------
	//public fields
	//----------------------------------------------------------
	/**	 * @brief holds data for positions and sizes of the hand tiles.	 */
	std::array<Rectangle, 14> recs;
	int size;

	/**
	 * @brief fills recs array with hand tiles rectangles.
	 * @param hand to be described
	 */
	HandTilesLayout(const Hand& hand);

	//----------------------------------------------------------
	//constants 
	//----------------------------------------------------------

	/**	@brief hand tile dimensions	 */
	static constexpr float WIDTH = 80;
	static constexpr float HEIGHT = 129;

	/** @brief position of the upper left corner of the hand*/
	static constexpr Vector2 POSITION = { 340,900 };

	/** @brief position of the drawn tile relative to the last hand tile*/
	static constexpr float DRAW_TILE_OFFSET = 20;

	/** @brief num of tiles including draw tile*/
	static constexpr int MAX_HAND_SIZE = 14;

	/** @brief num of tiles excluding draw tile*/
	static constexpr int HAND_SIZE = 13;

private:
	static Rectangle getTileRec(const Hand& hand, int index);
};

/**
 * @brief data structure that describes a layout for a meld
 * used to fill MeldsLayout with melds.
 */
struct MeldLayout {

	//----------------------------------------------------------
	//public fields
	//----------------------------------------------------------
	/**	 * @brief holds data for a specific meld size and location.	 */
	std::array<Rectangle, 4> recs;
	int size;


	MeldLayout() = default;
	/**
	 * @brief fills the fields with relevant parameters of the given meld.
	 * @param meld to be layed out.
	 * @param position desired position for the meld.
	 */
	MeldLayout(const Meld& meld, Vector2 position);


	//----------------------------------------------------------
	//constants 
	//----------------------------------------------------------
	
	/**	 * @brief discard tile dimensions	 */
	static constexpr float TILE_WIDTH = 60;
	static constexpr float TILE_HEIGHT = 87;

	/** * @on screen size of a triplet	 */
	static constexpr float TRIPLET_WIDTH = 2 * TILE_WIDTH + TILE_HEIGHT;

	static constexpr int KAN_TILE_NUM = 4;
	static constexpr int TRIPLET_TILE_NUM = 3;

	
private:
	/**
	 * @brief each of these changes recs vector to fit the corresponding meld type.
	 * @param meld to be layed out.
	 * @param position of the meld.
	 */
	void ponLayout(const Meld& meld, Vector2 position);
	void chiLayout(const Meld& meld, Vector2 position);
	void ankanLayout(const Meld& meld, Vector2 position);
	void daiminkanLayout(const Meld& meld, Vector2 position);
	void shouminkanLayout(const Meld& meld, Vector2 position);
	
};

/**
 * @brief uses above data structure to lay out an entire hand's
 * meld vector. used for displaying and input calculations.
 */
struct MeldsLayout {

	//----------------------------------------------------------
	//public fields
	//----------------------------------------------------------
	std::array<MeldLayout, 4> layouts;
	int size;


	//----------------------------------------------------------
	//constants 
	//----------------------------------------------------------

	//tile and meld on screen dimension:
	static constexpr float TILE_WIDTH = 60;
	static constexpr float TILE_HEIGHT = 87;
	static constexpr float TRIPLET_WIDTH = 2 * TILE_WIDTH + TILE_HEIGHT;
	static constexpr float DAIMINKAN_WIDTH = 3 * TILE_WIDTH + TILE_HEIGHT;
	static constexpr float SHOUMINKAN_WIDTH = TRIPLET_WIDTH;
	static constexpr float ANKAN_WIDTH = 4 * TILE_WIDTH;

	/**	 @brief position of first meld */
	static constexpr Vector2 MELDS_POS = { 1900,1080 - TILE_HEIGHT - 50 };

	/**	 @brief space between melds */
	static constexpr int MELD_SPACE = 10;

	static constexpr int MAX_MELD_NUM = 4;

	//----------------------------------------------------------
	//constuctor 
	//----------------------------------------------------------
	
	/**
	 * @brief fills in layouts vector with meld positions and dimensions.
	 * @param melds vector of the hand that is to be layed out.
	 */
	MeldsLayout(const std::vector<std::unique_ptr<Meld>>& melds);
};

struct discardsLayoutParams {
	Vector2 position;
	Vector2 colStep;
	Vector2 rowStep;
	Vector2 riichiOffset;
	Vector2 afterRiichiShift;
	float width;
	float height;
};

struct PlayerDiscardsLayout {
	static constexpr int MAX_DISCARDS_TILES = 24;
	std::array<Rectangle, MAX_DISCARDS_TILES> recs;
	int size;
	RelativePosition position;


	static constexpr int TILE_WIDTH = 60;
	static constexpr int TILE_HEIGHT = 87;
	static constexpr Vector2 MY_PILE_POS = { (1920 - 6 * TILE_WIDTH) / 2,630 };
	static constexpr Vector2 RIGHT_PILE_POS = { MY_PILE_POS.x + 6 * TILE_WIDTH,MY_PILE_POS.y - TILE_WIDTH };
	static constexpr Vector2 TOP_PILE_POS = { MY_PILE_POS.x + 5 * TILE_WIDTH, MY_PILE_POS.y - 6 * TILE_WIDTH - TILE_HEIGHT };
	static constexpr Vector2 LEFT_PILE_POS = { MY_PILE_POS.x - TILE_HEIGHT,MY_PILE_POS.y - 6 * TILE_WIDTH };
	static constexpr int TILES_IN_ROW = 6;
	static constexpr int PLAYERS_NUM = 4;

	static constexpr std::array < discardsLayoutParams, PLAYERS_NUM> posConsts = {{
		//self
		{MY_PILE_POS,{TILE_WIDTH,0},{0,TILE_HEIGHT},{0,TILE_HEIGHT - TILE_WIDTH},{-TILE_WIDTH + TILE_HEIGHT,0},TILE_WIDTH,TILE_HEIGHT},
		//left
		{LEFT_PILE_POS,{0,TILE_WIDTH},{-TILE_HEIGHT,0},{-TILE_HEIGHT + TILE_WIDTH,0},{0,-TILE_WIDTH + TILE_HEIGHT},TILE_HEIGHT,TILE_WIDTH},
		//top
		{TOP_PILE_POS,{-TILE_WIDTH,0},{0,-TILE_HEIGHT},{0,-TILE_HEIGHT + TILE_WIDTH},{-TILE_WIDTH + TILE_HEIGHT,0},TILE_WIDTH,TILE_HEIGHT},
		//right
		{RIGHT_PILE_POS,{0,-TILE_WIDTH},{+TILE_HEIGHT,0},{TILE_HEIGHT - TILE_WIDTH,0},{0,TILE_WIDTH - TILE_HEIGHT},TILE_HEIGHT,TILE_WIDTH},
	}
};


	PlayerDiscardsLayout() = default;
	PlayerDiscardsLayout(const Discards& discards, RelativePosition position);

};

struct GameDiscardsLayout {
	std::array< PlayerDiscardsLayout, Constants::PLAYERS_NUM> layouts;
	RelativePosition getRelativePosition(Wind perspective, Wind other);
	GameDiscardsLayout(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players);
	void drawHitBoxes() const;
};