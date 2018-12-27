#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"
//#include "Scheduler.hpp"

namespace km
{

// fontSize 24, 15 / 22, 14 / 18, 12

class Picture;

// Represent one piece of picture
class PictureElement
{
public:
    size_t getWordLength() { return word_.length(); }

PictureElement(sf::Texture& texture, sf::IntRect textureSectionRect,
		int index, std::wstring word, sf::Vector2f pos )
    : missed_(false)
    , revealed_(false)
    , active_(false)
    , index_(index)
    , word_(word)
    , nextLetter_(word.front())
    //, scheduler_(sf::seconds(3.f), []() {  })
{
    constexpr int charFontSize = 22;
    constexpr int charWidth = 14;
    constexpr int charHeight = 24;

    sprite_.setTexture(texture);
    sprite_.setTextureRect(textureSectionRect);
    sprite_.setPosition(pos);

    wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    wordText_.setPosition(sf::Vector2f(
    						pos.x + sprite_.getTextureRect().width / 2.f ,
							pos.y + sprite_.getTextureRect().height/ 2.f));
    wordText_.setString(word);
    wordText_.setCharacterSize(charFontSize);
    //wordText_.setColor(sf::Color::White);
    wordText_.setStyle(sf::Text::Bold);
    wordText_.setOrigin(0, 0);

    //timer_.restart();
    
    //shape.setSize(sf::Vector2f(word.length() * charWidth, charHeight));

    log_info("PictureElement:" << word_);
}

PictureElement(const PictureElement& pe)
	: sprite_(pe.sprite_)
	, word_(pe.word_)
	, nextLetter_(pe.nextLetter_)
	, index_(pe.index_)
	, active_(pe.active_)
	, missed_(pe.missed_)
	, revealed_(pe.revealed_)
{
    log_info("PictureElement CPYCTOR: " << word_.c_str());
}

~PictureElement()
{
    log_info("PictureElement DTOR:" << word_.c_str());
}

int getIndex() const { return index_; }
bool isRevealed() const { return revealed_; }
bool isActive() const { return active_; }

void setActive()
{
    active_ = true;
    //scheduler_.start();
}

std::wstring getWord() const
{
    return word_;
}

void reveal()
{
    active_ = false;
    revealed_ = true;
}

void miss()
{
    active_ = false;
    revealed_ = false;
}

void update(sf::Time deltaTime)
{
    //if (active_ && (timer_.getElapsedTime().asSeconds() >= lifeTime))
    //{
    //    miss();
        // play FAIL audio
    //}
}

void draw(sf::RenderTarget& renderer)
{
    if(revealed_)
        renderer.draw(sprite_);
    if(active_)
        renderer.draw(wordText_);
}

private:
    sf::Sprite sprite_;
    sf::Clock timer_;
    sf::Text wordText_;
    std::wstring word_;
    wchar_t nextLetter_;
    //Scheduler scheduler_;

    bool active_;	// is it current active element? Can by only one at time
    bool revealed_;	// is picture revealed as a whole?
    bool missed_;	// is it was missed?
    int index_;

    float lifeTime = 3.f;	// how long it will stay uncovered? TODO: not here
};

}
