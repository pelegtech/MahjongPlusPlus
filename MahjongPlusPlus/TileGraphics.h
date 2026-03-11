#pragma once
#include "raylib.h"
#include <string>
#include "GameTypes.h"
#include <iostream>
#include <memory>
#include "Layout.h"

//Forward declarations
class Tile;
class Hand;
class Discards;
class Meld;

/** @class HandTilesRenderer
* @brief in charge of drawing the hand tiles on screen.
* has data on each tile's position.
*/
class HandTilesRenderer {
public:
	//constants -------------------------------------------------------

	



	/** @brief num of tiles including draw tile*/
	static constexpr int MAX_HAND_SIZE = 14;

	/** @brief num of tiles excluding draw tile*/
	static constexpr int HAND_SIZE = 13;

	static constexpr int TILE_WIDTH_SRC = 80;
	static constexpr int TILE_HEIGHT_SRC = 129;
	static constexpr int MELD_TILE_WIDTH_SRC = 60;
	static constexpr int MELD_TILE_HEIGHT_SRC = 87;


	/**
	 * @brief loads in the textures to be used
	 * @param handTilesPath hand tiles file
	 * @param meldTilesPath meld tiles file
	 * @param meldTilesRPath meld tiles file but rotated to the right
	 */
	HandTilesRenderer(const char* handTilesPath, const char* meldTilesPath, const char* meldTilesRPath);

	/**
	 * @brief unloads textures.
	 */
	~HandTilesRenderer();

	

	/**
	 * @param tile to be draw
	 * @param layout position and size of tile to be drawn.
	 */
	void drawTile(const Tile& tile, Rectangle layout) const;
	
	/**
	 * @brief each of the functions below is used to draw the corresponding meld. 
	 * @param meld to be drawn. must be of corresponding meld type.
	 * @param layout 
	 */
	void drawPon(const Meld& meld,const MeldLayout& layout) const;

	void drawChi(const Meld& meld, const MeldLayout& layout) const;

	void drawAnkan(const Meld& meld, const MeldLayout& layout) const;
	
	void drawDaiminkan(const Meld& meld, const MeldLayout& layout) const;
	
	void drawShouminkan(const Meld& meld, const MeldLayout& layout) const;
	

	/**
	 * @brief uses functions above to draw any type of given meld.
	 * @param meld  to be drawn
	 * @param layout positions and sizes of the meld tiles.
	 */
	void drawMeld(const Meld& meld, const MeldLayout& layout) const;

	/**
	 * @brief uses hand tile functions and meld functions to draw the entire hand.
	 * @param hand to be drawn.
	 */
	void draw(const Hand& hand,const HandTilesLayout& handTilesLayout,
		const MeldsLayout& meldsLayout) const;

	/**
	 * @brief draws the tile hitboxes for debugging purposes.
	 * @param hand to be described.
	 */
	void drawHitBoxes(const Hand& hand, const HandTilesLayout& handTilesLayout) const;


	
	
	

private:

	Texture2D handTileTextures;
	Texture2D meldTileTextures;
	Texture2D meldTileTexturesR;

	/**
	 * @brief draws a tile in case of aka, helper function for draw tile.
	 * @param tile aka tile to be drawn 
	 * @param layout position and dimension
	 */
	void drawTileAka(const Tile& tile, Rectangle layout) const;
	void drawMeldTileAka(const Tile& tile, Rectangle layout) const;
	void drawMeldTileAkaRight(const Tile& tile, Rectangle layout) const;

	/**
	 * @brief draws one of the meld tiles, used for the meld drawing methodes.
	 * @param tile to be drawn
	 * @param layout position and size of the tile to be drawn
	 */
	void drawMeldTile(const Tile& tile, Rectangle layout) const;

	/**
	 * @brief draws the back of a tile, for ankan purposes.
	 * @param position of the tile.
	 */
	void drawMeldTileBack(Rectangle position) const;

	/**
	 * @brief draws a meld tile rotated 90 degrees right.
	 * @param tile to be drawn on it's side
	 * @param layout position and dimension of the tile on screen.
	 */
	void drawMeldTileRight(const Tile& tile, Rectangle layout) const;


	/** @brief akadora's texture relative position in the file*/
	static constexpr int AKA_PLACE_IN_FILE = 10;

	/**	 * @brief location of the back of the tile in the file	 */
	static constexpr int BACK_ROW_IN_FILE = 4;
	static constexpr int BACK_COL_IN_FILE = 8;

};

/** @class DiscardTilesRenderer
* @brief in charge of drawing the discard tiles on screen.
* has data on each tile's position.
*/
class DiscardTilesRenderer {
public:
	//constants-------------------------------
	static constexpr int TILE_WIDTH = 60;
	static constexpr int TILE_HEIGHT = 87;
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