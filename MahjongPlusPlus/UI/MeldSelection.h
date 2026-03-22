#pragma once
#include <vector>
#include "Core/GameTypes.h"
#include "raylib.h"
#include "Graphics/TileGraphics.h"
#include <exception>

struct MoveOption;

class MeldSelection {	
private:
	std::vector<MoveOption> options;
	std::vector<Rectangle> tilesRecs;
	Rectangle rec;
public:
	
	MeldSelection() = default;

	static constexpr float SPACE_BETWEEN_MELDS = 15.0f;
	static constexpr float HEIGHT = 100.0f;
	static constexpr float POSITION_Y = 600.0f;
	static constexpr float TILE_WIDTH = 60.0f;
	static constexpr float TILE_HEIGHT = 87.0f;
	static constexpr float BOX_OUTLINE_THICKNESS = 4.0f;


	void update(const std::vector<MoveOption>& inputOptions, MoveType filter);
	void draw(const DiscardTilesRenderer& renderer);
	MoveOption optionFromPosition(Vector2 pos) const;

	class optionsDoNotFit : public std::exception {
	public:
		const char* what() const noexcept override {
			return "the given options don't fit the screen";
		}
	};

	class tooManyTiles : public std::exception {
	public:
		const char* what() const noexcept override {
			return "the amount of tiles exceeds the amount of pre-registered options tiles.";
		}
	};
	class emptyOptions : public std::exception {
	public:
		const char* what() const noexcept override {
			return "cannot make this operation on an empty options vector";
		}
	};

};