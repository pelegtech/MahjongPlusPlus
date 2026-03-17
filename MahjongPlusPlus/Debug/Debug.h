#include "Core/Tile.h"
#include "Core/Wall.h"
#include "Core/Hand.h"
#include "Core/Player.h"
#include "Core/Meld.h"
#include "Core/Triplet.h"
#include "Core/Kan.h"
#include "Core/Game.h"
#include "Input/InputManager.h"
#include "Graphics/Graphics.h"
#include "Graphics/Paths.h"
#include "Input/Controller.h"
#include "Layouts/TileLayouts.h"
#include "raylib.h"
#include <array>
#include <memory>
#include <vector>
#include <iostream>

namespace Debug {

	Tile tileFromCode(const std::string& str, int copy);

	int tileNumFromCode(const std::string& str);


	Hand handFromCodes(
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
		const std::string& s14);

	std::unique_ptr<Meld> pon(const std::string& s);

	std::unique_ptr<Meld> chi(const std::string& s1, const std::string& s2, const std::string& s3);

	std::unique_ptr<Meld> ankan(const std::string& s);

	std::unique_ptr<Meld> daiminkan(const std::string& s);

	std::unique_ptr<Meld> shouminkan(const std::string& s);


	std::string windToStr(const Wind& wind);

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