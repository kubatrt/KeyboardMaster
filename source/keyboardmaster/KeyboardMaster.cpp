#include "KeyboardMaster.hpp"
#include "MainMenu.hpp"
#include "frameworkLib/ResourceManager/ResourceManager.hpp"
#include "frameworkLib/Utilities.hpp"


namespace km
{

namespace
{
constexpr uint WindowWidth = 1024;
constexpr uint WindowHeight = 768;
constexpr char WindotTitle[] = "KeyboardMaster";
constexpr uint FramerateLimit = 60;
}

KeyboardMaster::KeyboardMaster()
    : fw::GameBase({ WindowWidth , WindowHeight }, WindotTitle)
{
	LOG_DEBUG(WindotTitle << ": " << WindowWidth << "x" << WindowHeight);
    window_.setFramerateLimit(FramerateLimit);

    addComponent<fw::FPSCounter>();

    // Start game from MainMenu
    pushState<MainMenu>(*this);
}

void KeyboardMaster::update(sf::Time deltaTime)
{
    getCurrentState().update(deltaTime);
}

void KeyboardMaster::draw(sf::RenderTarget& renderer)
{
    getCurrentState().draw(window_);
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
