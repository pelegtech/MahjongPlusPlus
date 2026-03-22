#pragma once
#include "raylib.h"
#include "Core/GameTypes.h"
#include "Layouts/TileLayouts.h"
#include <iostream>
#include <memory>
#include <string>


//Forward declarations
class Tile;
class Hand;
class Discards;
class Meld;
class Wall;

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
	void drawHitBoxes( const HandTilesLayout& handTilesLayout) const;


	
	
	

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
	
	/**
	 * @brief the dimensions of each tile in the texture files.
	 */
	static constexpr int TILE_WIDTH_SRC = 60;
	static constexpr int TILE_HEIGHT_SRC = 87;


	/**
	 * @brief self and top tiles texture files uses vertical tiles dimensions,
	 * while left and right has the exact same dimensions but flipped horizontally.
	 */
	static constexpr std::array<Vector2, 4> SRC_DIMENSIONS = { {
			//self
			{TILE_WIDTH_SRC,TILE_HEIGHT_SRC},
			//left
			{TILE_HEIGHT_SRC,TILE_WIDTH_SRC},
			//top
			{TILE_WIDTH_SRC,TILE_HEIGHT_SRC},
			//right
			{TILE_HEIGHT_SRC,TILE_WIDTH_SRC}

		} };
	
	static constexpr int PLAYERS_NUM = 4;
	
	/**
	 * @brief loads textures from paths.
	 */
	DiscardTilesRenderer(const char* pathSelf, const char* pathLeft, const char* pathUp, const char* pathRight);

	/**
	 * @brief unloads textures.
	 */
	~DiscardTilesRenderer();

	/**
	 * @brief draws discards tile in case of aka tile. 
	 * @param tile to be drawn {5m,5p,5s}
	 * @param dest where to draw it. usually taken from a layout. 
	 * @param seat to determine angle. 
	 */
	void drawTileAka(const Tile& tile,Rectangle dest,RelativePosition seat) const;
	void drawTileAka(const Tile& tile, Rectangle dest) const;

	/**
	 * @brief draws discards tile.
	 * @param tile to be drawn {5m,5p,5s}
	 * @param dest where to draw it. usually taken from a layout.
	 * @param seat to determine angle.
	 */
	void drawTile(const Tile& tile, Rectangle dest, RelativePosition seat) const;
	void drawTile(const Tile& tile, Rectangle dest) const;

	/**
	 * @brief draws one player's discards pile.
	 * @param discards to be drawn.
	 * @param layout of the player's discards pile.
	 */
	void draw(const Discards& discards, const PlayerDiscardsLayout& layout) const;

	void highlightCurrentDiscard(const PlayerDiscardsLayout& layout) const;


private:

	std::array<Texture2D, 4> textures;


	/** @brief akadora's texture relative position in the file*/
	static constexpr int AKA_PLACE_IN_FILE = 10;
	

};

class DeadWallRenderer {
public:
	DeadWallRenderer(const char* dead_Wall_tiles);
	~DeadWallRenderer();

	void drawTile(const Tile& tile, Rectangle rec) const;

	void draw(const Wall& wall, const DeadWallLayout layout);
private:
	Texture2D deadWallTiles;
	static constexpr int AKA_PLACE_IN_FILE = 10;
	static constexpr float TILE_WIDTH_SRC = 60.0f;
	static constexpr float TILE_HEIGHT_SRC = 97.0f;
	static constexpr int BACK_PLACE_IN_FILE = 8;
	static constexpr float OUTER_BOX_WIDTH = TILE_WIDTH_SRC * 5 + 40;
	static constexpr float OUTER_BOX_HEIGHT = TILE_HEIGHT_SRC + 40;
	static constexpr float OUTER_BOX_OUTLINE_THICKNESS = 5;
	void drawTileAka(const Tile& tile, Rectangle rec) const;
	void drawTileBack(Rectangle rec);
};