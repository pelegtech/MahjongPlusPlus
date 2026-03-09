#pragma once
#include "Hand.h"
#include "Discards.h"
#include "GameTypes.h"
#include <vector>
#include "Wall.h"
#include "Triplet.h"
#include "Kan.h"
#include "Raylib.h"

struct MoveOption {
	MoveType type;
	std::vector<Tile> tiles;
	MoveOption(MoveType type, std::vector<Tile> tiles);

	class invalidOption : public std::exception {
	public:
		const char* what() const noexcept override {
			return "type does not match parameters";
		}
	};
};

class Player {
private:
	Hand hand;
	Discards discards;
	Wind wind;
	int score;
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

	/*std::vector<MoveOption> riichiOptions() const;
	std::vector<MoveOption> ponOptions(Tile discardedTile) const;
	std::vector<MoveOption> chiOptions(Tile discardedTile) const;
	std::vector<MoveOption> kanOptions(Tile discardedTile) const;
	MoveOption chosenMove(const std::vector<MoveOption>& options) const;
	void playRiichi(const MoveOption& option);
	void playTsumo(const MoveOption& option);
	void playRon(const MoveOption& option);
	void playDiscard(const MoveOption& option);
	void playPon(const MoveOption& option, Tile discardedTile, Wind otherWind);
	void playChi(const MoveOption& option, Tile discardedTile, Wind otherWind);
	void playAnkan(const MoveOption& option, Wall& wall);
	void playDaiminkan(const MoveOption& option, Tile discardedTile, Wind otherWind, Wall& wall);
	void playShouminkan(const MoveOption& option, Wall& wall);*/
};