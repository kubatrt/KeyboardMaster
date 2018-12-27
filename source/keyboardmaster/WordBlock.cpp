#include "WordBlock.hpp"

namespace km
{

namespace
{
float SpawnHorizontalPositions[5] = { 0.f, 200.f, 400.f, 600.f, 800.f };
}

WordBlock::WordBlock(int x, std::wstring word, sf::Vector2f velocity)
    : word_(word)
    , velocity_(velocity)
    , isAlive_(true)
{
    log_info("WordBlock CTOR wordblock:" << word);

    wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    wordText_.setString(word);
    wordText_.setCharacterSize(CHAR_FONT_SIZE);
    wordText_.setFillColor(sf::Color::White);
    wordText_.setStyle(sf::Text::Bold);

    wordText_.setPosition(static_cast<float>(x), 0.f);

    shape_.setPosition(static_cast<float>(x), 0.f);
    shape_.setFillColor(sf::Color::Blue); // TODO: random, depend on length
    shape_.setSize(sf::Vector2f(static_cast<float>(word.length() * CHAR_WIDTH), static_cast<float>(CHAR_HEIGHT)));
}

WordBlock::WordBlock(const WordBlock& wb)
	: word_(wb.word_)
	, velocity_(wb.velocity_)
	, isAlive_(wb.isAlive_)
{
    log_info("WordBlock CPYCTOR: " << word_);
}

WordBlock::~WordBlock()
{
    log_info("WordBlock DTOR:" << word_);
}

void WordBlock::update(sf::Time deltaTime)
{
    shape_.move(velocity_);
    wordText_.move(velocity_);
}

void WordBlock::draw(sf::RenderTarget& renderer)
{
    renderer.draw(shape_);
    renderer.draw(wordText_);
}

}
