#include "Animation.hpp"

namespace framework
{



namespace experimental
{
Animation::Animation(unsigned frameSize)
    : FRAME_SIZE(frameSize)
{
}

void Animation::addFrame(unsigned index, sf::Time delay)
{
    sf::IntRect bounds;
    bounds.top = 0;
    bounds.height = FRAME_SIZE;
    bounds.width = FRAME_SIZE;
    bounds.left = index * FRAME_SIZE;

    frames_.emplace_back(bounds, delay);
}


const sf::IntRect& Animation::getFrame()
{
    if (timer_.getElapsedTime() >= frames_[currentFrame_].delay)
    {
        timer_.restart();
        currentFrame_++;
        if (currentFrame_ == frames_.size())
            currentFrame_ = 0;
    }

    return frames_[currentFrame_].bounds;
}

}   // experimental
}   // framework