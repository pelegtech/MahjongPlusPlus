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
#include <fstream>
#include <string>
#include "Graphics/TileGraphics.h"

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
		const std::string& s13);

	std::unique_ptr<Meld> pon(const std::string& s);

	std::unique_ptr<Meld> chi(const std::string& s1, const std::string& s2, const std::string& s3);

	std::unique_ptr<Meld> ankan(const std::string& s);

	std::unique_ptr<Meld> daiminkan(const std::string& s);

	std::unique_ptr<Meld> shouminkan(const std::string& s);


	std::string windToStr(const Wind& wind);

	




	Wall presetHandWall(const Hand& hand);


}




class Log {
private:
	static std::ofstream& getStream();
public:
	static void init(); 

	static void add(const std::string& msg);

};