#include "WordBlock.hpp"
#include <algorithm>

namespace km
{

namespace
{

// Set color depend on word length, WordsColorTable[ Clamp(word.length - 2, 10) ]
sf::Color WordsLengthToColorTable[10] = {
		sf::Color::Green,	// 2
		sf::Color::Magenta,	// 3
		sf::Color::Blue,	// 4
		sf::Color::Magenta,	// 5
		sf::Color::Red,		// 6
		sf::Color::Magenta,	// 7
		sf::Color::Blue,	// 8
		sf::Color::Magenta,	// 9
		sf::Color::Red,		// 10 >
};

}

WordBlock::WordBlock(float x, std::wstring word, float velocityY)
    : word_(word)
    , velocity_(sf::Vector2f(0, velocityY))
    , isAlive_(true)
{
	meteorSprite_.setTexture(framework::ResourceHolder::get().textures.get("meteorBrown"));
	meteorSprite_.setOrigin(0,0);
	meteorSprite_.setPosition(x, 0);

	wordText_.setOrigin(0,0);
    wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    wordText_.setString(word);
    wordText_.setCharacterSize(CHAR_FONT_SIZE);
    wordText_.setFillColor(sf::Color::White);
    wordText_.setStyle(sf::Text::Bold);
    wordText_.setPosition(static_cast<float>(x), 0.f);

    auto shapeSize = sf::Vector2f(
    		static_cast<float>(word.length() * CHAR_WIDTH + 2),
			static_cast<float>(CHAR_HEIGHT + 2));
    auto shapeColor = WordsLengthToColorTable[std::clamp(static_cast<int>(word.length() - 2), 0, 9)];

    shape_.setPosition(x, 0.f);
    shape_.setFillColor(shapeColor);
    shape_.setSize(shapeSize);

	LOG_DEBUG("WordBlock CTOR: " << word << " pos: " << x << " vel: " << velocityY);
}

WordBlock::WordBlock(const WordBlock& wb)
	: word_(wb.word_)
	, velocity_(wb.velocity_)
	, isAlive_(wb.isAlive_)
{
    LOG_DEBUG("WordBlock CPYCTOR: " << word_);
}

WordBlock::~WordBlock()
{
    LOG_DEBUG("WordBlock DTOR:" << word_);
}

void WordBlock::update(sf::Time deltaTime)
{
    shape_.move(velocity_);
    meteorSprite_.move(velocity_);
    wordText_.move(velocity_);
}

void WordBlock::draw(sf::RenderTarget& renderer)
{
    //renderer.draw(shape_);
	renderer.draw(meteorSprite_);
    renderer.draw(wordText_);
}

}
