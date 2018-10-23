#include "MainMenu.hpp"
#include "CourseMenu.hpp"
#include "GameSate.hpp"
#include "../FrameworkLib/GUI/Button.hpp"
#include "../FrameworkLib/GUI/Textbox.hpp"

#include <iostream>
#include <string>
#include <memory>

namespace example
{

MainMenu::MainMenu(fw::GameBase& game)
    : StateBase(game)
    , testMenu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
    auto b = std::make_unique<fw::gui::Button>();
    b->setText("Course game");
    b->setFunction([&]() {
        game_.pushState<CourseMenu>(game_);
    });

    auto b2 = std::make_unique<fw::gui::Button>();
    b2->setText("Catch game");
    b2->setFunction([&] ()
    {
        game_.pushState<GameState>(game_);
    });

    auto b3 = std::make_unique<fw::gui::Button>();
    b3->setText("Gallery game");
    b3->setFunction([&] ()
    {

    });

    auto bquit = std::make_unique<fw::gui::Button>();
    bquit->setText("Quit");
    bquit->setFunction([&] ()
    {
        game_.close();
    });

    testMenu_.addWidget(std::move(b));
    testMenu_.addWidget(std::move(b2));
    testMenu_.addWidget(std::move(b3));
    testMenu_.addWidget(std::move(bquit));
}

void MainMenu::handleEvents(sf::Event e)
{
    testMenu_.handleEvent(e, game_.getWindow());

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.close();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;
    default:
        break;
    }
}

void MainMenu::update(sf::Time deltaTime)
{

}

void MainMenu::draw(sf::RenderTarget& renderer)
{
    testMenu_.draw(renderer);
}

}
