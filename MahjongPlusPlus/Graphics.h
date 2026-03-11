#pragma once
#include "raylib.h"
#include "Player.h"
#include "Hand.h"
#include "Tile.h"
#include "Discards.h"
#include "GameTypes.h"
#include <string>
#include <memory>
#include "TileGraphics.h"
#include "Paths.h"
#include "Layout.h"


/**
* @class Graphics
* @brief in charge of drawing and positioning the textures.
*/
class Graphics {
public:
	static constexpr int SCREEN_WIDTH = 1920;
	static constexpr int SCREEN_HEIGHT = 1080;
	static constexpr int HAND_SIZE = 14;
	static constexpr Vector2 TILES_COUNTER_POSITION = { 700,480 };
	static constexpr int TILES_COUNTER_SIZE = 50;
	


	Graphics() = default;

	/**
	* @brief creats the renderers objects and
	*	loads them with the correct file paths.
	*	loads textures for textures under graphics authority.
	*/
	void init();

	/** @brief draws the background using the loaded background texture*/
	void drawBackground();

	/** @brief uses handTilesRendered to draw the hand tiles
	*	@param hand to be drawn in the middle of the screen
	*/
	void drawHand(const Hand& hand,
		const HandTilesLayout handTilesLayout, const MeldsLayout meldsLayout) const;

	/** @brief uses discardTilesRendered to draw the discard piles
	*	@param hand to be drawn in the middle of the screen
	*/
	void drawDiscards(const Player& perspectivePayer, const Player& p2,const Player& p3,
		const Player& p4) const;

	/** @brief unload textures that are loaded by this class */
	void clean();

	/** @brief draws a counter of the amount of tiles left
	*/
	void drawTilesLeft(int tilesLeft);

	/**
	 * @brief draw mouse and hand tiles hitboxes for debug purposes
	 * @param hand to be drawn
	 */
	void drawTileHitBox(const Hand& hand, const HandTilesLayout& layout) const;

private:
	Texture2D background;
	Texture2D discardTiles;
	Texture2D buttons;
	std::unique_ptr<HandTilesRenderer> handTilesRenderer;
	std::unique_ptr<DiscardTilesRenderer> discardTilesRenderer;
};