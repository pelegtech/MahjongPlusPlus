#include "Debug/Debug.h"
#include "Graphics/TileGraphics.h"
#include "Layouts\TileLayouts.h"

Tile Debug::tileFromCode(const std::string& str, int copy)
{
	
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

int Debug::tileNumFromCode(const std::string& str)
{
	Tile temp = tileFromCode(str, 0);
	return temp.getId() / 4;
}

Hand Debug::handFromCodes(const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const std::string& s6, const std::string& s7, const std::string& s8, const std::string& s9, const std::string& s10, const std::string& s11, const std::string& s12, const std::string& s13)
{
	int hist[34] = { 0 };
	std::array<Tile, 13> tiles;

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




	tiles[0] = tileFromCode(s1, --hist[tileNumFromCode(s1)]);
	tiles[1] = tileFromCode(s2, --hist[tileNumFromCode(s2)]);
	tiles[2] = tileFromCode(s3, --hist[tileNumFromCode(s3)]);
	tiles[3] = tileFromCode(s4, --hist[tileNumFromCode(s4)]);
	tiles[4] = tileFromCode(s5, --hist[tileNumFromCode(s5)]);
	tiles[5] = tileFromCode(s6, --hist[tileNumFromCode(s6)]);
	tiles[6] = tileFromCode(s7, --hist[tileNumFromCode(s7)]);
	tiles[7] = tileFromCode(s8, --hist[tileNumFromCode(s8)]);
	tiles[8] = tileFromCode(s9, --hist[tileNumFromCode(s9)]);
	tiles[9] = tileFromCode(s10, --hist[tileNumFromCode(s10)]);
	tiles[10] = tileFromCode(s11, --hist[tileNumFromCode(s11)]);
	tiles[11] = tileFromCode(s12, --hist[tileNumFromCode(s12)]);
	tiles[12] = tileFromCode(s13, --hist[tileNumFromCode(s13)]);

	
	return Hand(tiles);

}

std::unique_ptr<Meld> Debug::pon(const std::string& s)
{
	Tile t1 = tileFromCode(s, 0);
	Tile t2 = tileFromCode(s, 1);
	Tile t3 = tileFromCode(s, 2);
	return std::make_unique<Pon>(t1, t2, t3, TileMarker::RIGHT);
}

std::unique_ptr<Meld> Debug::chi(const std::string& s1, const std::string& s2, const std::string& s3)
{
	int hist[34] = { 0 };
	hist[tileNumFromCode(s1)]++;
	hist[tileNumFromCode(s2)]++;
	hist[tileNumFromCode(s3)]++;
	Tile t1 = tileFromCode(s1, --hist[tileNumFromCode(s1)]);
	Tile t2 = tileFromCode(s2, --hist[tileNumFromCode(s2)]);
	Tile t3 = tileFromCode(s3, --hist[tileNumFromCode(s3)]);
	return std::make_unique<Chi>(t1, t2, t3, TileMarker::RIGHT);
}

std::unique_ptr<Meld> Debug::ankan(const std::string& s)
{
	Tile t1 = tileFromCode(s, 0);
	Tile t2 = tileFromCode(s, 1);
	Tile t3 = tileFromCode(s, 2);
	Tile t4 = tileFromCode(s, 3);
	return std::make_unique<Ankan>(t1, t2, t3, t4);
}

std::unique_ptr<Meld> Debug::daiminkan(const std::string& s)
{
	Tile t1 = tileFromCode(s, 0);
	Tile t2 = tileFromCode(s, 1);
	Tile t3 = tileFromCode(s, 2);
	Tile t4 = tileFromCode(s, 3);
	return std::make_unique<Daiminkan>(t1, t2, t3, t4, TileMarker::RIGHT);
}
std::unique_ptr<Meld> Debug::shouminkan(const std::string& s)
{
	Tile t1 = tileFromCode(s, 0);
	Tile t2 = tileFromCode(s, 1);
	Tile t3 = tileFromCode(s, 2);
	Tile t4 = tileFromCode(s, 3);

	return std::make_unique<Shouminkan>
		(t4, std::make_unique<Pon>(t1, t2, t3, TileMarker::RIGHT));
}

std::string Debug::windToStr(const Wind& wind)
{
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


void Debug::drawHitBoxes(const HandTilesLayout & handTilesLayout, const GameDiscardsLayout & gameDiscardsLayout)
{
	for (int i = 0; i < handTilesLayout.size;i++) {
		DrawRectangleLinesEx(handTilesLayout.recs[i], 4.0f, GOLD);
	}
	for (const auto& layout : gameDiscardsLayout.layouts) {
		for (int i = 0; i < layout.size; i++) {
			DrawRectangleLinesEx(layout.recs[i], 4.0f, GOLD);
		}
	}
	DrawCircleV(PlayerDiscardsLayout::MY_PILE_POS, 5.0f, RED);
	DrawCircleV(PlayerDiscardsLayout::RIGHT_PILE_POS, 5.0f, GREEN);
	DrawCircleV(PlayerDiscardsLayout::LEFT_PILE_POS, 5.0f, RED);
	DrawCircleV(PlayerDiscardsLayout::TOP_PILE_POS, 5.0f, RED);
}

void Debug::drawWallDebug(const DiscardTilesRenderer & renderer, const Wall & wall)
{
	Rectangle box = { WALL_BOX_POS.x,WALL_BOX_POS.y, TILES_IN_WALL_ROW * DiscardTilesRenderer::TILE_WIDTH_SRC + (2 * SPACE_TILE_BOX_SIDE),
		(TILES_IN_WALL_COL * DiscardTilesRenderer::TILE_HEIGHT_SRC) + ((TILES_IN_WALL_COL - 1) * SPACE_BETWEEN_ROWS) + (2 * SPACE_TILE_BOX_SIDE) };
	DrawRectangleRec(box, DARKGRAY);
	DrawRectangleLinesEx(box, 5, BLACK);
	for (int i = 0; i < Constants::TOTAL_TILES_NUM; i++) {
		Rectangle dest = { WALL_BOX_POS.x + SPACE_TILE_BOX_SIDE + (i % TILES_IN_WALL_ROW) * DiscardTilesRenderer::TILE_WIDTH_SRC,
		WALL_BOX_POS.y + SPACE_TILE_BOX_SIDE + ((i / (TILES_IN_WALL_ROW)) * (SPACE_BETWEEN_ROWS + DiscardTilesRenderer::TILE_HEIGHT_SRC))
			, DiscardTilesRenderer::TILE_WIDTH_SRC, DiscardTilesRenderer::TILE_HEIGHT_SRC };
		if (i > wall.getTail() || i < wall.getHead()) {
			renderer.drawTile(wall.getWallVector()[i], dest, RelativePosition::SELF, GRAY);
		}
		else {
			renderer.drawTile(wall.getWallVector()[i], dest, RelativePosition::SELF, WHITE);
		}
	}
}

Wall Debug::presetHandWall(const Hand& hand)
{
	//reserve space for vectors and initiate the tiles in sequence order
	std::vector<Tile> tiles;
	tiles.resize(136);
	
	for (int i = 0; i < 13; i++) {
		tiles[135 - i] = hand.getHandTile(i);
	}
	int j = 0;
	for (int i = 0; i < (136);i++) {
		Tile newTile(i);
		if (!hand.isTileInHandTiles(newTile)) {
			tiles[j++] = newTile;
		}
	}

	//wall shuffle using std functions
	std::random_device randomNumber;
	std::mt19937 randomizer(randomNumber());
	std::shuffle(tiles.begin(), tiles.end() -  13, randomizer);

	return Wall(tiles);
}





std::ofstream& Log::getStream()
{
	static std::ofstream logFile("gamelog.txt", std::ios::trunc);
	return logFile;
}

void Log::init()
{
	{
		getStream() << "----Game Start----\n";
	}
}

void Log::add(const std::string& msg)
{
	getStream() << msg << "\n";
}
