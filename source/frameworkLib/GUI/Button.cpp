#include <iostream>

#include "Button.hpp"


namespace framework
{
namespace gui
{

namespace buttonColor
{
sf::Color normal{ 52, 150, 220 };
sf::Color clicked{ 52, 190, 220 };
}

namespace
{
}


Button::Button(ButtonSize s)
{
    button_.setFillColor(buttonColor::normal);
    switch (s)
    {
        case ButtonSize::Thin:
            button_.setSize({ 256, 32 });
            break;

        case ButtonSize::Wide:
            button_.setSize({256, 64});
            break;

        case ButtonSize::Small:
            button_.setSize({128, 64});
            break;
    }

}

void Button::setFunction(Callback func)
{
    callback_ = func;
}

void Button::setText (const std::string& str)
{
    text_.setString(str);
    updateText();
}

void Button::setTexture (const sf::Texture& tex)
{
    button_.setTexture(&tex);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	if(button_.isRolledOn(window))
    {
		if (e.type == sf::Event::MouseButtonPressed)
		{	
			button_.setFillColor(buttonColor::clicked);
		}
        if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
				button_.setFillColor(buttonColor::normal);
                callback_();
            }
        }
    }
}

void Button::draw(sf::RenderTarget& renderer)
{
	/*if (isSelected())
	{
		selection_.setSize(button_.getSize());
		selection_.setPosition(button_.getPosition());
		selection_.setOutlineColor({255, 200, 50});
		selection_.setOutlineThickness(2);
		selection_.setFillColor(sf::Color::Transparent);
	}*/

    renderer.draw(button_);
    renderer.draw(text_);
	renderer.draw(selection_);
}

void Button::setPosition(const sf::Vector2f& pos)
{
    position_ = pos;

    button_.setPosition(position_);
    text_.setPosition(position_);
    updateText();
}

void Button::updateText()
{
    text_.setOrigin(text_.getGlobalBounds().width  / 2.f,
                     text_.getGlobalBounds().height / 2.f);

    text_.move(button_.getGlobalBounds().width  / 2.f,
                button_.getGlobalBounds().height / 2.5f);
}


sf::Vector2f Button::getSize() const
{
    return button_.getSize();
}

}
}
