#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "frameworkLib/IGameComponent.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"


namespace km
{

class TypingTextComponent : public framework::IGameComponent
{
public:
	TypingTextComponent(sf::Vector2f position, sf::Color color, std::wstring defualtText = "")
	: typedLetter_(''),
	  typedWord_(""),
	  color_(color),
	  position_(position)
	{
		typingTextUI_.setCharacterSize(24);
		typingTextUI_.setFillColor(color_);
		typingTextUI_.setPosition(position_);
		typingTextUI_.setString(defualtText);
		typingTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));
	}

	void update(sf::Time deltaTime) override
	{
	}

    void draw(sf::RenderTarget& renderer) override
    {
    }

    void handleTextEnteredEvent(const sf::Event& e)
    {
    	if (static_cast<int>(typedLetter_) == KeyCode::Enter)
    	{
    		typedWord_ = typingText_;
    		typingText_.clear();
    	}
    }

    void setPosition();
    void setColor();
    wchar_t getLastTypedLetter();
    std::wstring getLastTypedWord();

private:
    sf::Vector2f position_;
    sf::Color color_;
    wchar_t typedLetter_;
    std::wstring typedWord_;
    std::wstring typingText_;
    sf::Text typingTextUI_;
};

}
