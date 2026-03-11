#pragma once

class Hand;
class InputManager;
struct HandTilesLayout;


class Controller {
public:
	Controller() = default;
	virtual int decideDiscard(const Hand& hand, const HandTilesLayout& layout
		, const InputManager& input) const = 0;
};

class HumanController : public Controller {
public:
	HumanController() = default;
	virtual int decideDiscard(const Hand& hand, const HandTilesLayout& layout
		, const InputManager& input) const override;
};

class BotController : public Controller {
public:
	BotController() = default;
	virtual int decideDiscard(const Hand& hand, const HandTilesLayout& layout
		, const InputManager& input) const override;
};