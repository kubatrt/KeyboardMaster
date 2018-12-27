#include "KeyboardMaster.hpp"
#include "MainMenu.hpp"
#include "frameworkLib/ResourceManager/ResourceManager.hpp"

namespace km
{

constexpr uint WindowWidth = 1024;
constexpr uint WindowHeight = 768;

KeyboardMaster::KeyboardMaster()
    : fw::GameBase({ WindowWidth , WindowHeight }, "KeyboardMaster")
{
    window_.setFramerateLimit(60);
    pushState<MainMenu>(*this);
}

void KeyboardMaster::update(sf::Time deltaTime)
{
    getCurrentState().update(deltaTime);
    //fpsCounter_.update(deltaTime);
}

void KeyboardMaster::draw(sf::RenderTarget& renderer)
{
    window_.clear();

    getCurrentState().draw(window_);
    //fpsCounter_.draw(window_);

    window_.display();
}

void KeyboardMaster::handleEvents()
{
    sf::Event e;

    while (window_.pollEvent(e))
    {
        getCurrentState().handleEvents(e);

        switch (e.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        default:
            break;
        }
    }
}

}
