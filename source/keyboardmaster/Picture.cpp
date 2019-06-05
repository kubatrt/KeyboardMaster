#include <algorithm>
#include "Picture.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{

Picture::Picture(uint width, uint height, uint rows, uint cols)	// FIXME: width, height not used
    : dictionary_("data/words_01")
{
    std::cout << "Picture CTOR w: " << width << " h: " << height << std::endl;

    float pictureOffset = 4.f;

    texture_ = framework::ResourceHolder::get().textures.get("obraz_1");	// FIXME: move out from the inside Picture class?
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
            std::wcout << "Random word: " << word << std::endl;
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

    initialize();
}

void Picture::initialize()
{
    activeIndex_ = 0;
    elements_.at(activeIndex_)->setActive();
    indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));
    std::wcout << "Initialized picture" << std::endl;
}

void Picture::wordTyped(std::wstring typedWord)
{
    typedWords_++;
    std::wcout << "Index: " << activeIndex_ << std::endl;
    if (elements_.at(activeIndex_)->getWord() == typedWord)
    {
        elements_.at(activeIndex_)->reveal();
    }
    else
    {
        elements_.at(activeIndex_)->miss();
    }
    
    //if(indexesLeft.size() == 0)
    //    isComplete_ = true;

    if (activeIndex_ < elementsCount() - 1)
    {
        activeIndex_++;
        activeIndex_ =  indexesLeft.at(framework::RandomMachine::getRange<int>(0, indexesLeft.size() - 1));
        indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));

        elements_.at(activeIndex_)->setActive();
    }
    std::wcout << "Index end: " << activeIndex_ << std::endl;
}



bool Picture::isComplete()
{
    auto revealed = std::count_if(elements_.begin(), elements_.end(), 
        [&](std::shared_ptr<PictureElement>& e){ return e->isRevealed(); });
    return revealed == elementsCount();
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
