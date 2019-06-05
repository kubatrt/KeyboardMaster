#include <algorithm>
#include "Picture.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{

// FIXME: width, height are not used
Picture::Picture(uint rows, uint cols, AssetName picture)
    : dictionary_("data/words_01")
{
    float pictureOffset = 0.f;
    // Randomize image

    texture_ = framework::ResourceHolder::get().textures.get(picture);
    sprite_.setTexture(texture_);
    sprite_.setPosition(sf::Vector2f(pictureOffset, pictureOffset));

    elementsInRow_ = rows;
    elementsInCol_ = cols;
    elementsTotal_ = elementsInRow_ * elementsInCol_;

    int picElemWidth = texture_.getSize().x / elementsInRow_;
    int picElemHeight = texture_.getSize().y / elementsInCol_;
    size_.x = static_cast<float>(texture_.getSize().x);
    size_.y = static_cast<float>(texture_.getSize().y);

    uint index = 0;
    for (uint y = 0; y < elementsInCol_; ++y)
    {
        for (uint x = 0; x < elementsInRow_; ++x)
        {
            std::wstring word = dictionary_.getRandomWord();
            LOG_CRITICAL("Random word: " << word);
            int picElemPositionX = x * picElemWidth + pictureOffset;
            int picElemPositionY = y * picElemHeight + pictureOffset;
            // TODO: Check here shared_ptr, can be unique_ptr?
            auto picElem = std::make_shared<PictureElement>(texture_, sf::IntRect(x * picElemWidth, y * picElemHeight, picElemWidth, picElemHeight),
                  index, word, sf::Vector2f(static_cast<float>(picElemPositionX), static_cast<float>(picElemPositionY)));
            elements_.push_back(picElem);
            
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

    LOG_DEBUG("indexesLeft count: " << indexesLeft.size());
    for(auto index : indexesLeft)
    {
    	LOG_DEBUG("indexesLeft " << index);
    }
}

void Picture::wordTyped(std::wstring typedWord)
{
    LOG_DEBUG("wordTyped, activeIndex_: " << activeIndex_);

    if (elements_.at(activeIndex_)->getWord() == typedWord)
    {
        elements_.at(activeIndex_)->reveal();
    }
    else
    {
        elements_.at(activeIndex_)->miss();
    }

    if (indexesLeft.size() > 0)
    {
        activeIndex_ = indexesLeft.at(framework::RandomMachine::getRange<int>(0, indexesLeft.size() - 1));
        indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));
        elements_.at(activeIndex_)->setActive();
    }

    LOG_DEBUG("activeIndex_ new: " << activeIndex_ << " indexesLeft: " << indexesLeft.size());
}

uint Picture::reveleadElementsCount()
{
	uint revealedElements = std::count_if(elements_.begin(), elements_.end(),
	        [&](std::shared_ptr<PictureElement>& e){ return e->isRevealed(); });
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
