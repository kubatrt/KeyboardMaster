#include <iostream>
#include <cmath>
#include <vector>
#include <SFML\Graphics.hpp>

#include "gtest\gtest.h"

#include "..\FrameworkLib\Utilities.hpp"
#include "..\FrameworkLib\Util\Maths.hpp"

using namespace testing;
using namespace framework;
using namespace framework::charutils;

TEST(CharUtils, Captitalize)
{
	std::string exampleText = "warsaw";
	Capitalize capitalize; 
	capitalize(exampleText);
	EXPECT_STREQ("Warsaw", exampleText.c_str());
}

TEST(CharUtils, ToUpper)
{
	std::string exampleText = "text in lower case";
	ToUpper upper;
	upper(exampleText);
	EXPECT_STREQ("TEXT IN LOWER CASE", exampleText.c_str());
}

TEST(CharUtils, ToLower)
{
	std::string exampleText = "TEXT IN UPPER CASE";
	ToLower lower;
	lower(exampleText);
	EXPECT_STREQ("text in upper case", exampleText.c_str());
}

TEST(CharUtils, RemoveSpaces)
{
	std::string text = "This is text with spaces.";
	RemoveSpaces rs;
	rs(text);
	EXPECT_STREQ("Thisistextwithspaces.", text.c_str());
}

TEST(PrintVector, test)
{
	sf::Vector2f vector { 120.f, 240.f };
	printVec(vector); 
	std::cout << std::endl;
}

TEST(PrintVariadic, test)
{
	std::ostringstream oss;
	printVA(oss, "This", "is", "a", "test");

	EXPECT_STREQ(",This,is,a,test\n", oss.str().c_str());
}

TEST(MathTest, Collision2d)
{
	Point p(1,1);
	Rect rect(0, 0, 2, 2);
	EXPECT_TRUE(collision2d(p, rect));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    std::cin.get();
    return ret;
}