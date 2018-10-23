#pragma once

#include <functional>

#include "Widget.hpp"


namespace framework
{
namespace gui
{

class TextBox : public Widget
{
    public:
        TextBox(std::string& modString);

        void setLabel(const std::string& str);
        void setTexture(const sf::Texture& tex);

        void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
        void draw(sf::RenderTarget& renderer) override;
        void setPosition(const sf::Vector2f& pos) override;
        sf::Vector2f getSize() const override;

    private:
        void handleClick(sf::Event e, const sf::RenderWindow& window);
        void handleTextInput(sf::Event e);

        sf::Vector2f position_;

        Rectangle m_rect;
        Text text_;
        Text m_label;
        std::string* m_pModString;

        bool m_isActive = false;
};

}
}
