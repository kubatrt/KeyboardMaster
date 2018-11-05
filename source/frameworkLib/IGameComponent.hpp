#pragma once

#include <SFML/Graphics.hpp>

namespace framework
{

struct IGameComponent
{
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
};

}
