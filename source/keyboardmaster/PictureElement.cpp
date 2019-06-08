#include "PictureElement.hpp"
#include <algorithm>

namespace km
{

namespace
{
constexpr float TimeScalingFactor = 1.5f;
constexpr int CharFontSize {22};
}

PictureElement::PictureElement(sf::Texture& texture, sf::IntRect textureSectionRect,
		int index, std::wstring word, sf::Vector2f pos )
    : missed_(false)
    , revealed_(false)
    , active_(false)
    , index_(index)
    , word_(word)
    , nextLetter_(word.front())
	, scheduler_( sf::Time{sf::seconds( static_cast<float>(word.size() / TimeScalingFactor) )})	// not clamp, how long it stays depends on word length
{
	scheduler_.setCallback([&]() { miss(); LOG_DEBUG("PictureElement Callback(): " << word_)});

	// fontSize 24, 15 / 22, 14 / 18, 12


	sprite_.setTexture(texture);
	sprite_.setTextureRect(textureSectionRect);
	sprite_.setPosition(pos);

	wordText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
	wordText_.setPosition(sf::Vector2f(
							pos.x + sprite_.getTextureRect().width / 2.f ,
							pos.y + sprite_.getTextureRect().height/ 2.f));
	wordText_.setString(word);
	wordText_.setCharacterSize(CharFontSize);
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
    if(active_)
        renderer.draw(wordText_);
}

}


