#pragma once
#include "raylib.h"
#include "Core/Discards.h"
#include "Core/GameTypes.h"
#include <string>
#include <memory>
#include "Core/GameTypes.h"

class Player;
class Hand;
class Wall;
struct HandTilesLayout;
struct MeldsLayout;
struct GameDiscardsLayout;
class HandTilesRenderer;
class DiscardTilesRenderer;
struct PlayerDiscardsLayout;
class DeadWallRenderer;
struct DeadWallLayout;

/**
* @class Graphics
* @brief in charge of drawing and positioning the textures.
*/
class Graphics {
public:
	static constexpr int SCREEN_WIDTH = 1920;
	static constexpr int SCREEN_HEIGHT = 1080;
	static constexpr int HAND_SIZE = 14;
	static constexpr Vector2 TILES_COUNTER_POSITION = { 890,415 };
	static constexpr int TILES_COUNTER_SIZE = 20;
	static constexpr Vector2 MY_WIND_POS = { 950,570 };
	static constexpr Vector2 LEFT_WIND_POS = { 800,430 };
	static constexpr Vector2 RIGHT_WIND_POS = { 1110,430 };
	static constexpr Vector2 TOP_WIND_POS = { 950,300 };
	static constexpr int WIND_INDICATOR_SIZE = 30;

	Graphics();
	~Graphics();


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
	void drawHand(const Hand& hand,	const HandTilesLayout& handTilesLayout, const MeldsLayout& meldsLayout) const;

	/** @brief uses discardTilesRendered to draw the discard piles
	*	@param hand to be drawn in the middle of the screen
	*/
	void drawDiscards(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players
		,std::array<PlayerDiscardsLayout,Constants::PLAYERS_NUM> layouts) const;

	/** @brief unload textures that are loaded by this class */
	void clean();

	/** @brief draws a counter of the amount of tiles left
	*/
	void drawTilesLeft(int tilesLeft);

	/**
	 * @brief draw mouse and hand tiles hitboxes for debug purposes
	 * @param hand to be drawn
	 */
	void drawTileHitBox(const HandTilesLayout& layout) const;

	/**
	 * @brief draw on screen the letters {E,S,W,N} each representing respective player wind. 
	 * @param perspectiveWind wind of the perspective player.
	 */
	void drawWinds(Wind perspectiveWind) const;

	/**
	 * @brief draws the outlies for rectangles in discards pool
	 * @param layout of discards to be drawn.
	 */
	void drawDiscardsHitboxes(const GameDiscardsLayout& layout) const;

	/**
	 * @brief marks the last tile discarded.
	 * @param layout of the last player who discarded a tile.
	 */
	void highlightLastDiscard(const PlayerDiscardsLayout layout) const;

	
	DiscardTilesRenderer& getDiscardRenderer() const;

	void drawDeadWall(const Wall& wall, const DeadWallLayout& layout) const;

	void highlightDorasDiscards(const std::array<std::unique_ptr<Player>, Constants::PLAYERS_NUM>& players
		, std::array<PlayerDiscardsLayout, Constants::PLAYERS_NUM> layouts, const Wall& wall);

	void highLightDoraHand(const Hand& hand, const HandTilesLayout& handTilesLayout, const MeldsLayout& meldsLayout, const Wall& wall) const;

	void drawWallDebug(const Wall& wall) const;

private:
	
	Texture2D background;
	Texture2D discardTiles;
	std::unique_ptr<HandTilesRenderer> handTilesRenderer;
	std::unique_ptr<DiscardTilesRenderer> discardTilesRenderer;
	std::unique_ptr<DeadWallRenderer> deadWallRenderer;
	


};