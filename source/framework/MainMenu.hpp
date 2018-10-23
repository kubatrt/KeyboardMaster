#pragma once

#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/GUI/StackMenu.hpp"

namespace example
{

namespace fw = framework;

class MainMenu : public fw::StateBase
{
public:
    MainMenu(fw::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu testMenu_;
};

}
