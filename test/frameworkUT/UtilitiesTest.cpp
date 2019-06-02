#include <iostream>
#include <cmath>
#include <vector>
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/Util/Maths.hpp"

using namespace testing;
using namespace framework;
using namespace framework::charutils;


// TOOD: fs::Vector2 matcher


TEST(Math, middlePoint)
{
	sf::Vector2i p1(2, 4);
	sf::Vector2i p2(0, 0);
	sf::Vector2i pm;

	pm = framework::middlePoint(p1,p2);
	EXPECT_EQ(pm.x, 1);
	EXPECT_EQ(pm.y, 2);

	pm = framework::middlePoint(p2,p1);
	EXPECT_EQ(pm.x, 1);
	EXPECT_EQ(pm.y, 2);
}

TEST(Math, mirrorPoint)
{
	sf::Vector2i p1(2,2);
	sf::Vector2i p2 = framework::mirrorPoint(p1);
	EXPECT_EQ(-2, p2.x);
	EXPECT_EQ(-2, p2.y);
}

TEST(CharaUtils, Captitalize)
{
	std::string exampleText = "breslau";
	Capitalize capitalize; 
	capitalize(exampleText);

	EXPECT_STREQ("Breslau", exampleText.c_str());
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

TEST(Print, Vector)
{
	sf::Vector2f vector { 120.f, 240.f };
	std::ostringstream oss;
	printVec(oss, vector);

	EXPECT_STREQ("[120, 240]", oss.str().c_str());
}

TEST(Print, VariadicPack)
{
	std::ostringstream oss;
	printVA(oss, "This", "is", "a", "test");

	EXPECT_STREQ("[ This is a test]", oss.str().c_str());
}

TEST(General, Collision2D)
{
	Point p(1,1);
	Point p2(3,1);
	Rect rect(0, 0, 2, 2);

	EXPECT_TRUE(collision2d(p, rect));
	EXPECT_FALSE(collision2d(p2, rect));
}

