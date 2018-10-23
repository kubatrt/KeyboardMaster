#include "Widget.hpp"

namespace framework
{
namespace gui 
{

unsigned int Widget::selectionIdndexCounter = 0;
unsigned int Widget::currentSelectionIndex = 1;

sf::Vector2f itof(sf::Vector2i vec)
{
	return sf::Vector2f(static_cast<float>(vec.x), static_cast<float>(vec.y));
}

Widget::Widget()
	: selectionIndex_(++Widget::selectionIdndexCounter)
	, isSelected_(selectionIndex_ == Widget::currentSelectionIndex ? true : false)
	, isActive_(true)
{

}

// Text
Widget::Text::Text()
{
    setCharacterSize(Widget::defaultCharacterSize);
    setOutlineColor(sf::Color::Black);
    setFillColor(sf::Color::White);
    setFont(ResourceHolder::get().fonts.get("arial"));
}

//Rectangle
bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
{
    auto pos = sf::Mouse::getPosition((window));
    return getGlobalBounds().contains(itof(pos));
}

bool Widget::Rectangle::isClicked(sf::Event e, const sf::RenderWindow& window)
{
    if(isRolledOn(window))
	{
        if (e.type == sf::Event::MouseButtonReleased)
        {
            return e.mouseButton.button == sf::Mouse::Left;
        }
    }
    return false;
}

}
}