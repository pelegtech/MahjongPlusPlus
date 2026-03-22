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



class Controller {
public:
	Controller() = default;
	virtual int decideDiscard(const HandTilesLayout& layout
		, const InputManager& input) const = 0;
	virtual MoveType decideTypeAfterDiscard(const InputManager& input, 
		const CallSelection& selection) const = 0;
	virtual MoveOption decideOptionAfterDiscard(const InputManager& input,
	const MeldSelection& selection) const = 0;
	
};

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

class BotController : public Controller {
public:
	BotController() = default;
	virtual int decideDiscard( const HandTilesLayout& layout
		, const InputManager& input) const override;
	virtual MoveType decideTypeAfterDiscard(const InputManager& input,
		const CallSelection& selection) const override;
	virtual MoveOption decideOptionAfterDiscard(const InputManager& input,
		const MeldSelection& selection) const override;
};