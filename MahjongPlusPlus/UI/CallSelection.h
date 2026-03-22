#pragma once
#include <vector>
#include "Core/GameTypes.h"
#include "raylib.h"
#include <array>
#include <string>
#include "Button.h"

struct MoveOption;

class CallSelection {
private:
	std::array<bool, static_cast<int>(MoveType::COUNT)> existingTypes;
	std::array<Button, static_cast<int>(MoveType::COUNT)> buttons;
public:
	CallSelection() = default;

	static constexpr std::array<Vector2, static_cast<int>(MoveType::COUNT)> BUTTON_POSITIONS = { {
			//WAITING
			{-1.0f,-1.0f},
			//SKIP
			{1500,700},
			//PON
			{1500 + Button::DEFAULT_WIDTH,700},
			//CHI
			{1500 + 2 *Button::DEFAULT_WIDTH,700},
			//ANKAN
			{0,0},
			//DAIMINKAN
			{1500 + Button::DEFAULT_WIDTH,700 + Button::DEFAULT_HEIGHT},
			//SHOUMINKAN
			{0,0},
			//RIICHI
			{0,0},
			//TSUMO
			{0,0},
			//RON
			{0,0},
		} };
	static constexpr std::array< const char*, static_cast<int>(MoveType::COUNT)> TYPE_NAMES = { 
		"WAITING","SKIP","PON","CHI","KAN","KAN","KAN","RIICHI","TSUMO","RON"
	};
	
	
	void update(const std::vector<MoveOption>& options);
	void draw() const;
	MoveType typeFromPosition(Vector2 pos) const;


};