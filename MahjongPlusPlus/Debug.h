#pragma once
#include "Tile.h"
#include "Hand.h"
#include "Player.h"
#include "GameTypes.h"
#include "Meld.h"
#include <string>
#include "Triplet.h"
#include "Kan.h"

namespace Debug {

	inline Tile tileFromCode(const std::string& str, int copy) {
		int val = str[0] - '0';
		char c = str[1];
		Suit suit;
		switch (c) {
		case 'm':
			suit = Suit::MAN;
			break;
		case 'p':
			suit = Suit::PIN;
			break;
		case 's':
			suit = Suit::SOU;
			break;
		case 'z':
			suit = Suit::HONOR;
			break;
		case 'M':
			suit = Suit::MAN;
			break;
		case 'P':
			suit = Suit::PIN;
			break;
		case 'S':
			suit = Suit::SOU;
			break;
		case 'Z':
			suit = Suit::HONOR;
			break;
		default:
			throw std::invalid_argument("invalid suit");
		}
		return Tile::tileFromSpecs(suit, val, copy);
	}

	inline int tileNumFromCode(const std::string& str) {
		Tile temp = tileFromCode(str, 0);
		return temp.getId() / 4;
	}


	inline Hand handFromCodes(
		const std::string& s1,
		const std::string& s2,
		const std::string& s3,
		const std::string& s4,
		const std::string& s5,
		const std::string& s6,
		const std::string& s7,
		const std::string& s8,
		const std::string& s9,
		const std::string& s10,
		const std::string& s11,
		const std::string& s12,
		const std::string& s13,
		const std::string& s14) {
		Hand hand;
		int hist[34] = { 0 };
		hist[tileNumFromCode(s1)]++;
		hist[tileNumFromCode(s2)]++;
		hist[tileNumFromCode(s3)]++;
		hist[tileNumFromCode(s4)]++;
		hist[tileNumFromCode(s5)]++;
		hist[tileNumFromCode(s6)]++;
		hist[tileNumFromCode(s7)]++;
		hist[tileNumFromCode(s8)]++;
		hist[tileNumFromCode(s9)]++;
		hist[tileNumFromCode(s10)]++;
		hist[tileNumFromCode(s11)]++;
		hist[tileNumFromCode(s12)]++;
		hist[tileNumFromCode(s13)]++;
		hist[tileNumFromCode(s14)]++;

		hand.drawTile(tileFromCode(s1, --hist[tileNumFromCode(s1)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s2, --hist[tileNumFromCode(s2)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s3, --hist[tileNumFromCode(s3)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s4, --hist[tileNumFromCode(s4)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s5, --hist[tileNumFromCode(s5)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s6, --hist[tileNumFromCode(s6)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s7, --hist[tileNumFromCode(s7)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s8, --hist[tileNumFromCode(s8)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s9, --hist[tileNumFromCode(s9)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s10, --hist[tileNumFromCode(s10)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s11, --hist[tileNumFromCode(s11)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s12, --hist[tileNumFromCode(s12)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s13, --hist[tileNumFromCode(s13)]));
		hand.addDrawnTile();
		hand.drawTile(tileFromCode(s14, --hist[tileNumFromCode(s14)]));
		hand.addDrawnTile();

		return hand;
	}
	inline std::unique_ptr<Meld> pon(const std::string& s) {
		Tile t1 = tileFromCode(s,0);
		Tile t2 = tileFromCode(s,1);
		Tile t3 = tileFromCode(s,2);
		return std::make_unique<Pon>(t1, t2, t3, TileMarker::RIGHT);
	}
	inline std::unique_ptr<Meld> chi(const std::string& s1, const std::string& s2, const std::string& s3) {
		int hist[34] = { 0 };
		hist[tileNumFromCode(s1)]++;
		hist[tileNumFromCode(s2)]++;
		hist[tileNumFromCode(s3)]++;
		Tile t1 = tileFromCode(s1, --hist[tileNumFromCode(s1)]);
		Tile t2 = tileFromCode(s2, --hist[tileNumFromCode(s2)]);
		Tile t3 = tileFromCode(s3, --hist[tileNumFromCode(s3)]);
		return std::make_unique<Chi>(t1, t2, t3, TileMarker::RIGHT);
	}
	inline std::unique_ptr<Meld> ankan(const std::string& s) {
		Tile t1 = tileFromCode(s,0);
		Tile t2 = tileFromCode(s,1);
		Tile t3 = tileFromCode(s,2);
		Tile t4 = tileFromCode(s,3);
		return std::make_unique<Ankan>(t1, t2, t3,t4);
	}
	inline std::unique_ptr<Meld> daiminkan(const std::string& s) {
		Tile t1 = tileFromCode(s, 0);
		Tile t2 = tileFromCode(s, 1);
		Tile t3 = tileFromCode(s, 2);
		Tile t4 = tileFromCode(s, 3);
		return std::make_unique<Daiminkan>(t1, t2, t3, t4,TileMarker::RIGHT);
	}
	inline std::unique_ptr<Meld> shouminkan(const std::string& s) {
		Tile t1 = tileFromCode(s, 0);
		Tile t2 = tileFromCode(s, 1);
		Tile t3 = tileFromCode(s, 2);
		Tile t4 = tileFromCode(s, 3);
		
		return std::make_unique<Shouminkan>
			(t4,std::make_unique<Pon>(t1, t2, t3, TileMarker::RIGHT));
	}

	inline std::string windToStr(const Wind& wind) {
		switch (wind) {
		case (Wind::EAST):
			return "East";
			break;
		case(Wind::SOUTH):
			return "South";
			break;
		case(Wind::WEST):
			return "West";
			break;
		case(Wind::NORTH):
			return "North";
			break;
		}
	}

}




//Hand test_hand = Debug::handFromCodes
//("3p", "1p", "1p", "2p", "3p", "3p", "4p", "5p", "6p", "7p", "8p", "9p", "9p", "9p");
//std::cout << test_hand;
//std::vector<std::unique_ptr<Meld>> melds;
//melds.push_back(Debug::pon("5p"));
//melds.push_back(Debug::ankan("5s"));
//// melds.push_back(Debug::shouminkan("5m"));
//melds.push_back(Debug::daiminkan("4p"));
//
//std::vector<Tile> tiles;
//tiles.push_back(Debug::tileFromCode("5p", 0));
//tiles.push_back(Debug::tileFromCode("5p", 1));
//tiles.push_back(Debug::tileFromCode("1z", 1));
//tiles.push_back(Debug::tileFromCode("2z", 1));
//tiles.push_back(Debug::tileFromCode("3z", 1));
//Hand test_hand2 = Hand(std::move(tiles), std::move(melds));
//std::unique_ptr<Pon> pon1 = std::make_unique<Pon>(
//	Debug::tileFromCode("1p", 0),
//	Debug::tileFromCode("1p", 1),
//	Debug::tileFromCode("1p", 2), TileMarker::LEFT);
//std::unique_ptr<Pon> pon2 = std::make_unique<Pon>(
//	Debug::tileFromCode("5p", 0),
//	Debug::tileFromCode("5p", 1),
//	Debug::tileFromCode("5p", 2), TileMarker::RIGHT);
//std::unique_ptr<Pon> pon3 = std::make_unique<Pon>(
//	Debug::tileFromCode("5s", 0),
//	Debug::tileFromCode("5s", 1),
//	Debug::tileFromCode("5s", 2), TileMarker::MIDDLE);
//
//Shouminkan kan1(Debug::tileFromCode("1p", 3), std::move(pon1));
//Shouminkan kan2(Debug::tileFromCode("5p", 3), std::move(pon2));
//Shouminkan kan3(Debug::tileFromCode("5s", 3), std::move(pon3));
//
//HandTilesRenderer handTilesDebug(AssetPaths::handTiles, AssetPaths::meldTiles, AssetPaths::meldTilesR);