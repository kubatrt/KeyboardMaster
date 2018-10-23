#include "Textbox.hpp"


namespace framework
{
namespace gui
{

TextBox::TextBox(std::string& modString)
:   m_pModString (&modString)
{
    m_label.setCharacterSize(15);
    m_rect.setFillColor({52, 152, 219});
    m_rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str)
{
    m_label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    handleClick(e, window);
    handleTextInput(e);
}

void TextBox::draw(sf::RenderTarget& renderer)
{
	const sf::Color InActiveColor = { 52, 152, 219 };
	const sf::Color ActiveColor = { 82, 132, 239 };

    if (!m_isActive)
    {
        m_rect.setFillColor(InActiveColor);
    }
    else
    {
        m_rect.setFillColor(ActiveColor);
    }

    renderer.draw(m_rect);
    renderer.draw(m_label);
    renderer.draw(text_);
}

void TextBox::setPosition(const sf::Vector2f& pos)
{
    position_ = pos;

    m_rect.setPosition(position_);
    m_label.setPosition(position_.x,
		position_.y + m_label.getGlobalBounds().height - m_rect.getGlobalBounds().height / 2);
    text_.setPosition  (position_);
    text_.move(5.f, m_rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
    return  {m_rect.getSize().x,
             m_rect.getSize().y + m_label.getGlobalBounds().height};
}

void TextBox::handleClick (sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    if (m_rect.getGlobalBounds().contains(itof(pos)))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = true;
            }
        }
    }
    else
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = false;
            }
        }
    }
}

void TextBox::handleTextInput (sf::Event e)
{
    if (e.type == sf::Event::TextEntered && m_isActive)
    {
        //Get the key that was entered
        unsigned char k = e.text.unicode;

        //Test if it within the "Type-able keys eg aA to zZ and 0 to 9
        if (k >= 32 && k <= 127)
        {
            m_pModString->push_back(k);
        }
        else if (k == 8) //Backspace
        {
            //prevents popping back an empty string
            if (m_pModString->length() > 0)
                m_pModString->pop_back();
        }
        text_.setString(*m_pModString);
    }
}

}
}
