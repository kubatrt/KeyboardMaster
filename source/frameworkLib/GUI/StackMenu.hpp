#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Widget.hpp"

namespace framework
{
namespace gui
{

// TODO: extract widget container class
class StackMenu : public Widget
{
    public:
		StackMenu() = delete;
        StackMenu(const sf::Vector2f& position, float offset = 25.f);
        ~StackMenu() = default;
        StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        void addWidget(std::unique_ptr<Widget>);
        void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
        void draw(sf::RenderTarget& renderer) override;
        virtual void setPosition(const sf::Vector2f& pos) override;
        virtual sf::Vector2f getSize() const override;

    protected:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> widgets_;	// owner of Widgets
        sf::RectangleShape background_;
        sf::Vector2f basePosition_;
        sf::Vector2f baseSize_;
        float offset_;

private:
	void resize(const Widget& widget);
};

}
}
