#pragma once
#include "Core/Hand.h"
#include "Core/Discards.h"
#include "Core/GameTypes.h"
#include "Core/Wall.h"
#include "Core/Triplet.h"
#include "Core/Kan.h"
#include "Core/MoveOption.h"
#include "Raylib.h"
#include <vector>



class Player {
private:
	Hand hand;
	Discards discards;
	Wind wind;
	int score;
	std::vector<MoveOption> options;


public:
	Player() = default;
	void setWind(Wind wind);
	void setScore(int score);
	void Draw(Wall& wall);
	void addTileFromWall(Wall& wall);
	void Discard(int index);
	void sortHand();
	const Hand& getHand() const;
	Discards& getDiscards();
	const Discards& getDiscards() const;
	const Wind& getWind() const;
	const Tile& getLastDiscard() const;
	TileMarker relativePlace(Wind otherWind);
	void updateOptionsDiscard(const Tile& tile, const Wind& otherWind);
	void resetOptions();
	const std::vector<MoveOption>& getOptions() const;

	static constexpr int PLAYERS_NUM = 4;


	//options:
	void executeOption(const MoveOption& option, Discards& discards, const Wind& otherWind);
	bool ponOptions(const Tile& discard);
	void executePon(const MoveOption& chosenOption, Discards& discards, const Wind& Otherwind);
	bool chiOptions(const Tile& discard, const Wind& wind);
	void executeChi(const MoveOption& chosenOption, Discards& discards, const Wind& Otherwind);

	RelativePosition getRelativePosition(const Wind& other) const;

};