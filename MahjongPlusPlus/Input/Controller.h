#pragma once
#include <vector>
#include "Core/GameTypes.h"

class Hand;
class InputManager;
struct HandTilesLayout;
struct MoveOption;
class DiscardTilesRenderer;
class CallSelection;
class MeldSelection;


/**
 * @brief this class manages the way choses are made from different kinds of players such as a human player or bot player.
 * a human player's choice would be determined using input while a bot will choose based off of algorithm.
 */
class Controller {
public:
	Controller() = default;

	/**
	 * @brief allows the player to choose which tile to discard from the hand.
	 * @param layout of the hand tiles to calculate collision.
	 * @param input manager to recieve input from player.
	 * @return index of tile chosen. [0,handTilesNum] while the last index represents drawn tile.
	 */
	virtual int decideDiscard(const HandTilesLayout& layout
		, const InputManager& input) const = 0;
	/**
	 * @brief allows the player to choose a meld type such as pon or chi and or skip and so on, depending on options available. 
	 * @param input manager to recieve input from human player.
	 * @param selection menu to calculate collision and choices available.
	 * @return the type chosen
	 */
	virtual MoveType decideTypeAfterDiscard(const InputManager& input, 
		const CallSelection& selection) const = 0;
	/**
	 * @brief allows the player to choose out of the meld options available. example: 6s was discarded, choose between 5s4s chi or 5s7s chi.
	 * @param input manager to recieve input from human player.
	 * @param selection to calculate collision and see the choices available.
	 * @return option selected
	 */
	virtual MoveOption decideOptionAfterDiscard(const InputManager& input,
	const MeldSelection& selection) const = 0;
	
};

/**
 * @brief calculate choices based on input manager. (human player mouse or keyboard input)
 */
class HumanController : public Controller {
public:
	HumanController() = default;
	virtual int decideDiscard(const HandTilesLayout& layout
		, const InputManager& input) const override;

	virtual MoveType decideTypeAfterDiscard(const InputManager& input,
		const CallSelection& selection) const override;

	virtual MoveOption decideOptionAfterDiscard(const InputManager& input,
		const MeldSelection& selection) const override;
};
/**
 * @brief calculate choics based on alogirthm.
 */
class BotController : public Controller {
public:
	BotController() = default;

	/**
	 * @return always chooses the drawn tile. tsumogiri.
	 */
	virtual int decideDiscard( const HandTilesLayout& layout
		, const InputManager& input) const override;
	/**
	 * @return always chooses skip 
	 */
	virtual MoveType decideTypeAfterDiscard(const InputManager& input,
		const CallSelection& selection) const override;
	/**
	 * @return always chooses skip 
	 */
	virtual MoveOption decideOptionAfterDiscard(const InputManager& input,
		const MeldSelection& selection) const override;
};