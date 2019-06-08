#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"

namespace km
{

constexpr uint CHAR_FONT_SIZE = 22;
constexpr uint CHAR_WIDTH = 14;
constexpr uint CHAR_HEIGHT = 24;


class WordBlock
{
public:
    WordBlock(float x, std::wstring word, float velocityY);
    WordBlock(const WordBlock&);
    WordBlock& operator=(const WordBlock&);
    ~WordBlock();

    sf::RectangleShape getShape() const { return shape_; }
    void setAlive(bool alive) { isAlive_ = alive; }
    bool isAlive() const { return isAlive_; }

    std::wstring getWord() const { return word_; }
    size_t getWordLength() const { return word_.length(); }

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

private:
//  wchar_t nextLetter_;
    sf::RectangleShape shape_;
    sf::Text wordText_;
    sf::Vector2f velocity_;
    std::wstring word_;
    bool isAlive_;
};

} // km
