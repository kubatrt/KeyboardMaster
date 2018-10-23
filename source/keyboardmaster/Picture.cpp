#include <algorithm>
#include "Picture.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace km
{

Picture::Picture(const sf::Texture& texture, uint width, uint height, uint rows, uint cols)
    : dictionary_("D:/Workspace/Projects/Framework/Debug/data/words_01")  // data/words_01
    , isComplete_(false)
{
    std::cout << "PICTURE Width: " << width << " Height: " << height << std::endl;

    texture_ = texture;
    // res/textures/obraz_1.png
    //texture_.loadFromFile("D:/Workspace/Projects/Framework/Debug/res/textures/obraz_1.png");
    sprite_.setTexture(texture_);
    sprite_.setPosition(sf::Vector2f(0, 0));

    elementsInRow_ = rows;
    elementsInCol_ = cols;
    elementsTotal_ = elementsInRow_ * elementsInCol_;

    int picElemWidth = texture_.getSize().x / elementsInRow_;
    int picElemHeight = texture_.getSize().y / elementsInCol_;

    int index = 0;
    for (uint y = 0; y < elementsInCol_; ++y)
    {
        for (uint x = 0; x < elementsInRow_; ++x)
        {
            std::wstring word = dictionary_.getRandomWord();
            std::wcout << "Random word: " << word << std::endl;
            int picElemPositionX = x * picElemWidth;
            int picElemPositionY = y * picElemHeight;

            auto picElem = std::make_shared<PictureElement>(texture_, sf::IntRect(x * picElemWidth, y * picElemHeight, picElemWidth, picElemHeight),
                  index, word, sf::Vector2f(static_cast<float>(picElemPositionX), static_cast<float>(picElemPositionY)));
            elements_.push_back(picElem);
            
            indexesLeft.push_back(index);
            index++;
        }
    }

    init();
}

void Picture::typedWord(std::wstring typedWord)
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

void Picture::init()
{
    activeIndex_ = 0;
    elements_.at(activeIndex_)->setActive();
    indexesLeft.erase(std::remove(indexesLeft.begin(), indexesLeft.end(), activeIndex_));
    
    std::wcout << "Init" << std::endl;
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