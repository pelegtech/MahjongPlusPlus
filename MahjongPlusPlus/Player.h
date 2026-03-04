#pragma once
#include "Hand.h"
#include "Discards.h"
#include "GameTypes.h"



class Player {
private:
	Hand hand;
	Discards discards;
	Wind wind;
	int score;
public:
	Player(Wind wind, int score);
	void Riichi();
	void Draw();
	void playPon(Discards otherDiscards, Wind otherWind);
	void playChi(Discards otherDiscards, Wind otherWind);
	void playAnkan();
	void playDaiminkan(Discards otherDiscards, Wind otherWind);
	void playShouminkan(Discards otherDiscards, Wind otherWind);
};