#pragma once
#include "Hand.h"
#include "Discards.h"
#include "GameTypes.h"
#include <vector>
#include "Wall.h"
#include "Triplet.h"
#include "Kan.h"
#include "Raylib.h"
#include "MoveOption.h"


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
	void Discard(int index);
	void sortHand();
	const Hand& getHand() const;
	const Discards& getDiscards() const;
	const Wind& getWind() const;
	TileMarker relativePlace(Wind otherWind);
	void updateOptionsDiscard(const Tile& tile);

	static constexpr int PLAYERS_NUM = 4;


	//options:
	bool ponOptions(const Tile& discard);
	void executePon(const MoveOption& chosenOption, Discards& discards, const Wind& Otherwind);


};