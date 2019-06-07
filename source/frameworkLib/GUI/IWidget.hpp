#pragma once

#include <SFML/Graphics.hpp>

namespace framework
{
namespace gui
{

// Virtuality: http://www.gotw.ca/publications/mill18.htm
struct IWidget
{
	virtual ~IWidget() = default;

    virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;

    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual sf::Vector2f getSize() const = 0;
};

}
}   // framework
