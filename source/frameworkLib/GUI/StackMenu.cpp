#include <iostream>
#include "StackMenu.hpp"

#include "../ResourceManager/ResourceHolder.hpp"

namespace framework
{
namespace gui
{

namespace
{
//constexpr float defaultY = 95.f;
constexpr float defaultWidth = 300.f;
constexpr float defaultHeight = 25.f;
//constexpr float offset = 25.f;
}


StackMenu::StackMenu(const sf::Vector2f& position, float offset)
    : basePosition_(position)
    , baseSize_(defaultWidth, defaultHeight)
    , offset_(offset)
{
    background_.setFillColor({127, 127, 127});
    background_.setPosition(basePosition_.x - baseSize_.x / 2.f, basePosition_.y - offset_);
    background_.setSize(baseSize_);
    std::wcout << "StackMenu CTOR " << basePosition_.x << ", " << basePosition_.y << std::endl;
}

StackMenu::StackMenu(StackMenu&& other)
    : widgets_(std::move(other.widgets_))
    , background_(std::move(other.background_))
    , basePosition_(other.basePosition_)
    , baseSize_(other.baseSize_)
{
    std::wcout << "StackMenu COPY CTOR " << std::endl;
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    std::wcout << "StackMenu MOVE CTOR " << std::endl;
    widgets_  = std::move(other.widgets_);
    background_ = std::move(other.background_);
    basePosition_ = other.basePosition_;
    baseSize_  = other.baseSize_;
    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    widgets_.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    // move widget accordingly menu bounds
    widget.setPosition({basePosition_.x - widget.getSize().x / 2, basePosition_.y});

    // set size of menu accordingly to wigets inside
    basePosition_.y += widget.getSize().y + offset_;
    baseSize_.y += widget.getSize().y + offset_;
    background_.setSize(baseSize_);
}

void StackMenu::setPosition(const sf::Vector2f& pos)
{
    background_.setPosition(pos);
}

sf::Vector2f StackMenu::getSize() const
{
    return background_.getSize();
}

void StackMenu::alignSize()
{
	// align background size to added widgets
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : widgets_)
    {
        widget->handleEvent(e, window);
    }
}

void StackMenu::draw(sf::RenderTarget& renderer)
{
    renderer.draw(background_);

    for (auto& widget : widgets_)
    {
        widget->draw(renderer);
    }
}

}
}
