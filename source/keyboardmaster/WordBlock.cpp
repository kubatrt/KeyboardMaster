#include "WordBlock.hpp";

namespace km
{

namespace
{
    static float spawnHorizontalPositions[5] = { 0.f, 200.f, 400.f, 600.f, 800.f };
}


WordBlock::WordBlock(int spawnX, std::wstring word, sf::Vector2f velocity)
    : word_(word)
    , velocity_(velocity)
    , alive_(true)
{
    log_info("CTOR wordblock:" << word);

    wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    wordText_.setString(word);
    wordText_.setCharacterSize(CHAR_FONT_SIZE);
    wordText_.setFillColor(sf::Color::White);
    wordText_.setStyle(sf::Text::Bold);

    
    int spawnHorizontalPos = spawnX;
    wordText_.setPosition(static_cast<float>(spawnHorizontalPos), 0.f);

    shape_.setPosition(static_cast<float>(spawnX), 0.f);
    shape_.setFillColor(sf::Color::Blue); // TODO: random, depend on length
    shape_.setSize(sf::Vector2f(static_cast<float>(word.length() * CHAR_WIDTH), static_cast<float>(CHAR_HEIGHT)));
}

WordBlock::WordBlock(const WordBlock& wordBlock)
{
    log_info("CCTOR constructor: " << word_);
}

WordBlock::~WordBlock()
{
    log_info("DTOR wordblock:" << word_);
}


std::wstring WordBlock::getWord() const 
{ 
    return word_;
}

void WordBlock::setAlive(bool alive) 
{ 
    alive_ = alive;
}

bool WordBlock::isAlive() const 
{ 
    return alive_;
}


size_t WordBlock::getWordLength() const
{
    return word_.length();
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