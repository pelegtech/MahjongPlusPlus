#include "pch.h"
#include "../MahjongPlusPlus/Core/Hand.h"
#include "../MahjongPlusPlus/Debug/Debug.h"


TEST(HandValidationTests, ValidStandardHand1) {
	Hand testHand = Debug::handFromCodes("1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "1p", "2p", "3p", "1m");
	testHand.sortHand();
	testHand.drawTile(Debug::tileFromCode("1m",1));

  EXPECT_TRUE(testHand.getValidHands().size() > 0);
}