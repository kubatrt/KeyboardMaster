#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "../FrameworkLib/Utilities.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

constexpr uint CHAR_FONT_SIZE = 22;
constexpr uint CHAR_WIDTH = 14;
constexpr uint CHAR_HEIGHT = 24;


class WordBlock
{
public:
    WordBlock(int spawnX, std::wstring word, sf::Vector2f velocity);
    WordBlock(const WordBlock& wordBlock);
    ~WordBlock();

    sf::RectangleShape getShape() const { return shape_; }
    void setAlive(bool alive);
    bool isAlive() const;
    std::wstring getWord() const;
    size_t getWordLength() const ;

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

private:
//    wchar_t nextLetter_;
    std::wstring word_;

    sf::Vector2f velocity_;
    sf::RectangleShape shape_;
    sf::Text wordText_;
    bool alive_;
};

} // km