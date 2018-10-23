#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace framework
{

struct Animation
{
    std::string name_;
    std::string textureName_;
    std::vector<sf::IntRect>    frames_;
    sf::Time    duration_;
    bool looping_;

    Animation(const std::string& name, const std::string& textureName,
        const sf::Time& duration, bool looping)
        : name_(name_)
        , textureName_(textureName)
        , duration_(duration)
        , looping_(looping)
    {}

    void addFrame(sf::Vector2i startFrom, sf::Vector2i frameSize, unsigned int frames)
    {
    }
};

namespace experimental
{

// TODO
class Animation
{
    public:
        struct Frame
        {
            Frame(const sf::IntRect& bnds, sf::Time dlay)
                : bounds(bnds)
                , delay(dlay) {}

            sf::IntRect bounds;
            sf::Time delay;
        };

        Animation(unsigned frameSize);

        void addFrame(unsigned index, sf::Time delay);
        const sf::IntRect& getFrame();

    private:
        sf::Clock timer_;
        std::vector<Frame> frames_;
        unsigned currentFrame_ = 0;
        const unsigned FRAME_SIZE;
};

}   // experimental
}   // framework