#include "CatchGame.hpp"
#include "MainMenu.hpp"
#include "CourseMenu.hpp"
#include "../FrameworkLib/ResourceManager/ResourceManager.hpp"

namespace example
{

CatchGame::CatchGame()
    : fw::GameBase({ 1280, 720 }, "Catch game")
{
    window_.setFramerateLimit(60);  // instead of separate fixedUpdate
    pushState<MainMenu>(*this);
}

void CatchGame::update(sf::Time deltaTime)
{
    getCurrentState().update(deltaTime);
    fpsCounter_.update(deltaTime);
}

void CatchGame::draw(sf::RenderTarget& renderer)
{
    window_.clear();

    getCurrentState().draw(window_);
    fpsCounter_.draw(window_);

    window_.display();
}

void CatchGame::handleEvents()
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
