#include "gtest/gtest.h"
#include "StateBaseMock.hpp"
#include "../FrameworkLib/StateBase.hpp"


using namespace framework;
using namespace testing;

class StateBaseFixture : public Test
{
public:
	StateBaseFixture()
		//: game_()
	{

	}

	void SetUp()
	{

	}

	void TearDown()
	{

	}

private:
	//Game game_;
};


TEST_F(StateBaseFixture, shallCreateInstance)
{
	
	//StateBaseMock state(game);
	EXPECT_TRUE(true);
}