#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../FrameworkLib/Utilities.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"
//#include "Scheduler.hpp"

namespace km
{

// fontSize 24, 15 / 22, 14 / 18, 12

class Picture;

class PictureElement// : public Rectangle
{
public:
    size_t getWordLength() { return word_.length(); }

PictureElement(sf::Texture& texture, sf::IntRect textureRect, int index, std::wstring word, 
    sf::Vector2f pos )
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
    sprite_.setTextureRect(textureRect);
    sprite_.setPosition(pos);

    //sf::Font font;
    wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial")); 
    // fw::ResourceHolder::get().fonts.get("arial")
    wordText_.setString(word);
    wordText_.setCharacterSize(charFontSize);
    //wordText_.setColor(sf::Color::White);
    wordText_.setStyle(sf::Text::Bold);
    wordText_.setOrigin(0, 0);

    wordText_.setPosition(sf::Vector2f( pos.x + sprite_.getTextureRect().width / 2.f ,
        pos.y + sprite_.getTextureRect().height/ 2.f));
    //timer_.restart();
    
    //shape.setSize(sf::Vector2f(word.length() * charWidth, charHeight));

    log_info("PictureElement:" << word_);
}

PictureElement(const PictureElement& pictureElement)
{
    this->sprite_ = pictureElement.sprite_;
    this->index_ = pictureElement.index_;
    this->word_ = pictureElement.word_;
    this->nextLetter_= pictureElement.nextLetter_;

    log_info("PictureElement CPY: " << word_.c_str());
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

    bool active_;
    bool revealed_;
    bool missed_;
    int index_;
    float lifeTime = 3.f;
};

}	// KM
