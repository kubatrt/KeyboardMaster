#include "PictureElement.hpp"

namespace km
{

PictureElement::PictureElement(sf::Texture& texture, sf::IntRect textureSectionRect,
		int index, std::wstring word, sf::Vector2f pos )
    : missed_(false)
    , revealed_(false)
    , active_(false)
    , index_(index)
    , word_(word)
    , nextLetter_(word.front())
{
	// fontSize 24, 15 / 22, 14 / 18, 12
	const int charFontSize {22};
	const int charWidth {14};
	const int charHeight {24};

	sprite_.setTexture(texture);
	sprite_.setTextureRect(textureSectionRect);
	sprite_.setPosition(pos);

	wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
	wordText_.setPosition(sf::Vector2f(
							pos.x + sprite_.getTextureRect().width / 2.f ,
							pos.y + sprite_.getTextureRect().height/ 2.f));
	wordText_.setString(word);
	wordText_.setCharacterSize(charFontSize);
	wordText_.setStyle(sf::Text::Bold);
	wordText_.setOrigin(0, 0);

	//timer_.restart();
	//shape.setSize(sf::Vector2f(word.length() * charWidth, charHeight));

	LOG_DEBUG("PictureElement: " << index_ << " : " << word_);
}

PictureElement::PictureElement(const PictureElement& pe)
	: sprite_(pe.sprite_)
	, word_(pe.word_)
	, nextLetter_(pe.nextLetter_)
	, index_(pe.index_)
	, active_(pe.active_)
	, missed_(pe.missed_)
	, revealed_(pe.revealed_)
{
	LOG_DEBUG("PictureElement CPYCTOR: " << word_.c_str());
}

PictureElement::~PictureElement()
{
	LOG_DEBUG("PictureElement DTOR:" << word_.c_str());
}

void PictureElement::reveal()
{
    active_ = false;
    revealed_ = true;
}

void PictureElement::miss()
{
    active_ = false;
    revealed_ = false;
}

void PictureElement::update(sf::Time deltaTime)
{
    //if (active_ && (timer_.getElapsedTime().asSeconds() >= lifeTime))
    //{
    //    miss();
        // play FAIL audio
    //}
}

void PictureElement::draw(sf::RenderTarget& renderer)
{
    if(revealed_)
        renderer.draw(sprite_);
    if(active_)
        renderer.draw(wordText_);
}

}


