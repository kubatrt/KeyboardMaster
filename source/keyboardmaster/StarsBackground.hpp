#pragma once

#include <SFML/Graphics.hpp>


namespace kb
{

struct Star
{
    sf::Uint32  size_;
    sf::Vector2i position_;
};

class StarsBackground
{
public:
    StarsBackground() {};

    void update(sf::Time deltaTime){};
    void draw(sf::RenderTarget& renderer){};

private:
    sf::Color   color_;
    sf::Uint32  starsNumber_;
    sf::Vector2i velocity_;
    std::vector<Star>   stars_;
};

}