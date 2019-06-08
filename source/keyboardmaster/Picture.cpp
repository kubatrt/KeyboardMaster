#include <algorithm>
#include "Picture.hpp"
#include "frameworkLib/Utilities.hpp"
#include "SoundPlayer.hpp"

namespace km
{

Picture::Picture(uint rows, uint cols, AssetName picture, AssetName wordsFile)
    : dictionary_(wordsFile)
{
    texture_ = framework::ResourceHolder::get().textures.get(picture);
    sprite_.setTexture(texture_);
    float pictureOffset = 0.f;
    sprite_.setPosition(sf::Vector2f(pictureOffset, pictureOffset));

    elementsInRow_ = rows;
    elementsInCol_ = cols;
    elementsTotal_ = elementsInRow_ * elementsInCol_;

    int picElemWidth = texture_.getSize().x / elementsInCol_;
    int picElemHeight = texture_.getSize().y / elementsInRow_;
    size_.x = static_cast<float>(texture_.getSize().x);
    size_.y = static_cast<float>(texture_.getSize().y);

    uint index = 0;
    for (uint y = 0; y < elementsInRow_; ++y)
    {
        for (uint x = 0; x < elementsInCol_; ++x)
        {
            std::wstring word = dictionary_.getRandomWord();
            LOG_CRITICAL("Random word: " << word);
            int picElemPositionX = x * picElemWidth + pictureOffset;
            int picElemPositionY = y * picElemHeight + pictureOffset;

            auto picElem = std::make_unique<PictureElement>(texture_,
            		sf::IntRect(x * picElemWidth, y * picElemHeight, picElemWidth, picElemHeight),
					sf::Vector2f(static_cast<float>(picElemPositionX), static_cast<float>(picElemPositionY)),
					index, word);
            elements_.push_back(std::move(picElem));
            
            indexesLeft.push_back(index);
            index++;
        }
    }

    LOG_DEBUG("Picture CTOR " << picture.c_str() << " " << rows << "x" << cols);
    LOG_DEBUG("Picture elements count: " << elements_.size());
    initialize();
}

void Picture::initialize()
{
    activeIndex_ = 0;	// starting element
    indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));
    elements_.at(activeIndex_)->setActive();

    LOG_DEBUG("initialize() indexesLeft count: " << indexesLeft.size());
}

void Picture::nextPictureElement()
{
	if (indexesLeft.size() > 0)
	{
		activeIndex_ = indexesLeft.at(framework::RandomMachine::getRange<int>(0, indexesLeft.size() - 1));
		indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));
		elements_.at(activeIndex_)->setActive();
	}
	LOG_DEBUG("nextPictureElement activeIndex_: " << activeIndex_ << " indexesLeft: " << indexesLeft.size());
}

bool Picture::wordTyped(std::wstring typedWord)
{
    LOG_DEBUG("wordTyped() activeIndex_: " << activeIndex_);
    bool result = false;
    if (elements_.at(activeIndex_)->getWord() == typedWord)
    {
        elements_.at(activeIndex_)->reveal();
        SoundPlayer::get().play("reveal");
        result = true;
    }
    else
    {
        elements_.at(activeIndex_)->miss();
        SoundPlayer::get().play("mistake");
        result = false;
    }
    nextPictureElement();
    return result;
}

bool Picture::isAnyActiveElement()
{
	return std::any_of(elements_.begin(), elements_.end(), [&](auto& e) { return e->isActive();});
}

uint Picture::reveleadElementsCount()
{
	uint revealedElements = std::count_if(elements_.begin(), elements_.end(),
	        [&](auto& e){ return e->isRevealed(); });
	return revealedElements;
}

bool Picture::isComplete()
{
    return reveleadElementsCount() == elementsCount();
}


void Picture::update(sf::Time deltaTime)
{
    for (auto &element : elements_)
    {
        element->update(deltaTime);
    }

    if(elements_.at(activeIndex_)->isMissed())
    {
    	// missed beacause of elapsed time
    	SoundPlayer::get().play("mistake");
    	nextPictureElement();
    }
}


void Picture::draw(sf::RenderTarget& renderer)
{
    for (auto &element : elements_)
    {
        element->draw(renderer);
    }

    if(visible_)
        renderer.draw(sprite_);
}

}
