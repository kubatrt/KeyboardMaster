#include "PictureElement.hpp"
#include <algorithm>

namespace km
{

namespace
{
constexpr float ExpirationTimeFactor = 1.5f;
constexpr int FontSize = 22;
}

PictureElement::PictureElement(sf::Texture& texture, sf::IntRect textureSectionRect, sf::Vector2f position,
		uint index, std::wstring word)
    : missed_(false)
    , revealed_(false)
    , active_(false)
    , index_(index)
    , word_(word)
    , nextLetter_(word.front())
	, scheduler_( sf::Time{sf::seconds( static_cast<float>(word.size() / ExpirationTimeFactor) )})	// not clamp, how long it stays depends on word length
{
	scheduler_.setCallback([&]() { miss(); });

	sprite_.setTexture(texture);
	sprite_.setTextureRect(textureSectionRect);
	sprite_.setPosition(position);

	wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
	wordText_.setPosition(sf::Vector2f(
			position.x + sprite_.getTextureRect().width / 2.f ,
			position.y + sprite_.getTextureRect().height/ 2.f));
	wordText_.setString(word);
	wordText_.setCharacterSize(FontSize);
	wordText_.setStyle(sf::Text::Bold);
	wordText_.setOrigin(0, 0);

	LOG_DEBUG("PictureElement: " << index_ << " : " << word_);
}

PictureElement::~PictureElement()
{
	LOG_DEBUG("PictureElement DTOR:" << word_);
}

void PictureElement::reveal()
{
    active_ = false;
    revealed_ = true;
    missed_ = false;
}

void PictureElement::miss()
{
    active_ = false;
    revealed_ = false;
    missed_ = true;
    wordText_.setFillColor(sf::Color(100,100,100));
}

void PictureElement::update(sf::Time deltaTime)
{
	if(!active_)
		return;

	scheduler_.update();
}

void PictureElement::draw(sf::RenderTarget& renderer)
{
    if(revealed_)
        renderer.draw(sprite_);
    if(active_ || missed_)
        renderer.draw(wordText_);
}

}


