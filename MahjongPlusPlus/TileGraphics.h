#pragma once
#include "raylib.h"
#include <string>
#include "GameTypes.h"


//Forward declarations
class Tile;
class Hand;
class Discards;


/** @class HandTilesRenderer
* @brief in charge of drawing the hand tiles on screen.
* has data on each tile's position.
*/
class HandTilesRenderer {
public:
	//constants -------------------------------------------------------
	
	static constexpr int TILE_WIDTH = 80;
	static constexpr int TILE_HEIGHT = 129;

	/** @brief position of the upper left corner of the hand*/
	static constexpr Vector2 POSITION = { 340,900 };

	/** @brief position of the drawn tile relative to the last hand tile*/
	static constexpr int DRAW_TILE_OFFSET = 20;

	/** @brief num of tiles including draw tile*/
	static constexpr int MAX_HAND_SIZE = 14;

	/** @brief num of tiles excluding draw tile*/
	static constexpr int HAND_SIZE = 13;

	/**@param path - to the tiles png */
	HandTilesRenderer(const char* path);

	/** @brief unloads texture */
	~HandTilesRenderer();

	/**
	* @param tile must be one of the three aka tiles (id) 16/52/88
	* @param position on screen
	*/
	void drawTileAka(const Tile& tile, Vector2 position) const;

	/**
	* @param tile to be drawn
	* @param position on screen
	*/
	void drawTile(const Tile& tile, Vector2 position) const;

	/**
	* @brief draw a hand on the bottom middle of the screen
	* @param hand to be drawn
	*/
	void draw(const Hand& hand) const;


	/**
	* @param position of the mouse pointer
	* @return index of tile from leftmost to rightmost
	*/
	static int getTileIndexFromPosition(Vector2 position);

	

private:

	Texture2D textures;

	/** @brief akadora's texture relative position in the file*/
	static constexpr int AKA_PLACE_IN_FILE = 10;

};

/** @class DiscardTilesRenderer
* @brief in charge of drawing the discard tiles on screen.
* has data on each tile's position.
*/
class DiscardTilesRenderer {
public:
	//constants-------------------------------
	static constexpr int TILE_WIDTH = 80;
	static constexpr int TILE_HEIGHT = 116;
	static constexpr float FRONT_ORIENTATION = 0.0f;
	static constexpr float RIGHT_ORIENTATION = 270.0f;
	static constexpr float TOP_ORIENTATION = 180.0f;
	static constexpr float LEFT_ORIENTATION = 90.0f;
	static constexpr Vector2 MY_PILE_POS = { 700,545 };
	static constexpr Vector2 RIGHT_PILE_POS = { 1280,720 };
	static constexpr Vector2 TOP_PILE_POS = { 1180,400 };
	static constexpr Vector2 LEFT_PILE_POS = { 600,240 };
	static constexpr int TILES_IN_ROW = 6;
	static constexpr int RELATIVE_POSITION_MINE = 0;
	static constexpr int RELATIVE_POSITION_LEFT = 1;
	static constexpr int RELATIVE_POSITION_TOP = 2;
	static constexpr int RELATIVE_POSITION_RIGHT = 3;
	static constexpr int PLAYERS_NUM = 4;
	

	/**@param path - to the tiles png */
	DiscardTilesRenderer(const char* path);

	/** @brief unloads texture */
	~DiscardTilesRenderer();

	/**
	* @param tile must be one of the three aka tiles (id) 16/52/88
	* @param position on screen
	*/
	void drawTileAka(const Tile& tile, Vector2 position, float orienation) const;

	/**
	* @param tile to be drawn
	* @param position on screen
	*/
	void drawTile(const Tile& tile, Vector2 position, float orienation) const;

	/**
	* @brief draws player's perspective own discards
	* @param discards player's discard pool
	*/
	void drawDiscardsMine(const Discards& discards) const;

	/**
	* @brief draws player's perspective top player discards
	* @param discards top player's discard pool
	*/
	void drawDiscardsTop(const Discards& discards) const;

	/**
	* @brief draws player's perspective right player discards
	* @param discards right player's discard pool
	*/
	void drawDiscardsRight(const Discards& discards) const;

	/**
	* @brief draws player's perspective left player discards
	* @param discards left player's discard pool
	*/
	void drawDiscardsLeft(const Discards& discards) const;

	/**
	* @brief draws a discard pool relative to the player's wind
	* @param discard pool to be drawn
	* @param playerWind the perspective player's own wind
	* @param discardsWind the wind of the player who owns the discard pool
	*/
	void draw(const Discards& discards, Wind playerWind, Wind discardsWind) const;

private:

	Texture2D textures;

	/** @brief akadora's texture relative position in the file*/
	static constexpr int AKA_PLACE_IN_FILE = 10;
	

};