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


/**
 * @brief manages player's state. a player has score, hand, discards pile and assigned wind. also keeps track of different move options
 * avialable to the player at each turn.
 */
class Player {
private:

	//-----------------------------------------------------------------------
	//PRIVATE FIELDS
	//-----------------------------------------------------------------------


	Hand hand;
	Discards discards;
	Wind wind;
	int score;

	/**
	 * @brief available actions, resets each turn.
	 */
	std::vector<MoveOption> options;


public:
	class handAlreadyInitiated : public std::exception {
	public:
		const char* what() const noexcept override {
			return "trying to initiate an hand that's already been initiated";
		}
	};




	//---------------------------------------------------------------------------
	//PUBLIC METHODES
	//--------------------------------------------------------------------------
	
	Player() = default;
	
	/**
	 * @brief take a tile from the wall and add it to your hand's drawn tile position.
	 * @param wall to take the tile from.
	 */
	void Draw(Wall& wall);

	/**
	 * @brief add a tile directly to the hand in a sorted manner. used in game initialization.
	 * @param wall to take the tile from.
	 */
	void addTileFromWall(Wall& wall);

	/**
	 * @brief remove a tile from the hand and add it to the discards pile. 
	 * @param index of the tile to be discarded. [0,freeTilesNum], last index is for drawn tile.
	 */

	void Discard(int index);
	/**
	 * @brief sort hand by tile id.
	 */
	void sortHand();
	

	//----------------------------------------------------------------------------------------------------------
	//GETTERS & SETTERS
	//----------------------------------------------------------------------------------------------------------

	/**
	 * @brief both functions take another player's wind and convert it to realtive position {self,left,top,right}
	 * @param otherWind 
	 * @return 
	 */
	TileMarker relativeMarker(Wind otherWind) const;
	RelativePosition getRelativePosition(const Wind& other) const;

	
	
	const Discards& getDiscards() const;
	const Wind& getWind() const;

	/**	 * @return last tile discarded (to calculate other players options)	 */
	const Tile& getLastDiscard() const;
	const Hand& getHand() const;
	Discards& getDiscards();
	void setWind(Wind wind);
	void setScore(int score);


	//-------------------------------------------------------------------------------
	// MEHTODES RELATED TO OPTIONS
	//--------------------------------------------------------------------------------

	const std::vector<MoveOption>& getOptions() const;
	/**
	 * @brief clear the options vector (used each turn)
	 */
	void resetOptions();
	/**
	 * @brief update options based on last discard made. uses all of the other functions.
	 * @param tile to calculate options based off of.
	 * @param otherWind to see if chi is available or not.
	 */
	void updateOptionsDiscard(const Tile& tile, const Wind& otherWind);

	/**
	 * @brief executes chosen option.
	 * @param option to be executed.
	 * @param discards to take tile from.
	 * @param otherWind for tile marker.
	 */
	void executeOption(const MoveOption& option, Discards& discards, const Wind& otherWind);

	/**
	 * @brief calculates pon options and add them directly to options vector. makes different options for akadora.
	 * @param discard to calculate options based off of.
	 * @return true if any option was found.
	 */
	bool ponOptions(const Tile& discard);
	
	/**
	 * @brief create a pon from a discarded tile and two hand tiles.
	 * @param chosenOption pon option chosen.
	 * @param discards to take extra tile from.
	 * @param Otherwind for tile marker.
	 */
	void executePon(const MoveOption& chosenOption, Discards& discards, const Wind& Otherwind);

	/**
	 * @brief calculate chi options and add them directly to options vector. makes different options for akadora.
	 * @param discard to calculate chi options on.
	 * @param wind to check if chi is even valid.
	 * @return true if options were found.
	 */
	bool chiOptions(const Tile& discard, const Wind& wind);

	/**
	 * @brief create a chi from two hand tiles and an external tile.
	 * @param chosenOption the chi option chosen by the player.
	 * @param discards to take the extra tile from.
	 * @param Otherwind for tile marker. (supposedly always left tile marker).
	 */
	void executeChi(const MoveOption& chosenOption, Discards& discards, const Wind& Otherwind);

	bool daiminkanOptions(const Tile& discard);

	void executeDaiminkan(const MoveOption& chosenOption, Discards& discards, const Wind& otherWind);

	//we use rvalue reference because we definitely will steal the input hand and replace the player's hand with it.
	void initHand(Hand&& inputHand);
};