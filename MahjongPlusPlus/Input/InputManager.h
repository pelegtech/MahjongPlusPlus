#pragma once
#include "Raylib.h"
#include "Core/GameTypes.h"

struct HandTilesLayout;
class CallSelection;
class MeldSelection;
class MoveOption;

/**
 * @brief takes player input such as mouse position and uses rectangle collision to 
 *	check which option was chosen by the player.
 */
class InputManager {
public:
	InputManager() = default;
	/**
	 * @brief calculates which tile was chosen based off of rectangle collision.
	 * @param handTilesLayout gets layout of hand to see how many hand tiles are available and calculate collision.
	 * @return index of tile chosen [0,handTilesNum] last index represents drawn tile. returns -1 if none were chosen.
	 */
	int tileIndexFromClick( const HandTilesLayout& handTilesLayout) const;

	/**
	 * @brief to check which call is chosen skip, pon, chi etc.
	 * @param selection of calls available.
	 * @return type chosen. returns type MoveOption::WAITING if none were chosen.
	 */
	MoveType typeFromClick(const CallSelection& selection) const;

	/**
	 * @brief to check which option was chosen example: 6s was discarded, chi with 4s5s or 5s7s.
	 * @param selection to check which options are available.
	 * @return option chosen. returns a move option without tiles and type WAITING if none were chosen.
	 */
	MoveOption OptionFromClick(const MeldSelection& selection) const;
};