
#include "UI/MeldSelection.h"
#include "Core/MoveOption.h"
#include "UI/Button.h"
#include <cmath>

void MeldSelection::update(const std::vector<MoveOption>& inputOptions, MoveType filter)
{
	
	options.clear();
	tilesRecs.clear();


	float width = SPACE_BETWEEN_MELDS;
	for (const auto& option : inputOptions) {
		if (option.type == filter) {
			options.push_back(option);
			width += TILE_WIDTH * option.size();
			width += SPACE_BETWEEN_MELDS;
		}
	}


	float currX = std::floor((Constants::SCREEN_WIDTH - width) / 2);
	float Y = std::floor(POSITION_Y + ((HEIGHT - TILE_HEIGHT) / 2));

	rec.x = currX;
	rec.y = POSITION_Y;
	rec.width = width;
	rec.height = HEIGHT;
	
	currX += SPACE_BETWEEN_MELDS;
	for (const auto& option : options) {
		for(int i  = 0; i < option.size() ; i++){
			Rectangle currRec = { currX,Y,TILE_WIDTH, TILE_HEIGHT };
			tilesRecs.push_back(currRec);
			currX += TILE_WIDTH;
		}

		currX += SPACE_BETWEEN_MELDS;
	}
}

void MeldSelection::draw(const DiscardTilesRenderer& renderer)
{
	Color semiTransparentGray = Fade(GRAY, 0.5f);
	DrawRectangleRec(rec, semiTransparentGray);
	DrawRectangleLinesEx(rec, BOX_OUTLINE_THICKNESS, BLACK);
	
	int i = 0;
	for (const auto& option : options) {
		for(int j = 0; j < option.size(); j++)
			renderer.drawTile(option.tiles[j], tilesRecs[i++]);
	}
}

MoveOption MeldSelection::optionFromPosition(Vector2 pos) const
{
	if (options.size() <= 0) {
		throw emptyOptions();
	}
	int size = options[0].size();
	for (int i = 0; i < tilesRecs.size(); i++) {
		if (CheckCollisionPointRec(pos, tilesRecs[i])) {
			return options[(i / size)];
		}
	}
	return MoveOption(MoveType::WAITING);
}

