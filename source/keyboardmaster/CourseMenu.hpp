#pragma once

#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/StateBase.hpp"
#include "frameworkLib/GUI/StackMenu.hpp"

namespace km
{

namespace fw = framework;

class CourseMenu : public fw::StateBase
{
public:
    CourseMenu(fw::GameBase& game);
    ~CourseMenu() = default;

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu menuLeft_;
    fw::gui::StackMenu menuRight_;
};

}
