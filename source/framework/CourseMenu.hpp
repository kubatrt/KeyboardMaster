#pragma once

#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"
#include "../FrameworkLib/GameBase.hpp"

namespace example
{

namespace fw = framework;

class CourseMenu : public framework::StateBase
{
public:
    CourseMenu(framework::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu courseMenu_;
};

}
