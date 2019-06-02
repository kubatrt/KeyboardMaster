#include <iostream>
#include <string>
#include <memory>

#include "MainMenu.hpp"
#include "CourseGame.hpp"
#include "CourseMenu.hpp"
#include "GalleryGame.hpp"
#include "WordsAttackGame.hpp"
#include "WritingGame.hpp"
#include "frameworkLib/GUI/Button.hpp"
#include "frameworkLib/GUI/Textbox.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

MainMenu::MainMenu(fw::GameBase& game)
    : StateBase(game)
    , menu_({ game.getWindow().getSize().x / 2.f, 90.f })
	, metronome_(80)
{
	std::cout << "MainMenu" << std::endl;


    auto b = std::make_unique<fw::gui::Button>();
    b->setText("Go to course");
    b->setFunction([&] ()
    {
        game_.pushState<CourseMenu>(game_);
    });

    auto b2 = std::make_unique<fw::gui::Button>();
    b2->setText("Words attack!");
    b2->setFunction([&] ()
    {
        game_.pushState<WordsAttackGame>(game_);
    });

    auto b3 = std::make_unique<fw::gui::Button>();
    b3->setText("Gallery");
    b3->setFunction([&] ()
    {
        game_.pushState<GalleryGame>(game_, sf::Vector2u{5, 4});
    });


    auto b4 = std::make_unique<fw::gui::Button>();
    b4->setText("Writing");
    b4->setFunction([&] ()
    {
        std::string articlesFiles[] = {
            "data/art_01.txt",
            "data/art_02.txt",
            "data/art_03.txt",
            "data/art_04.txt"
        };
        int pick = fw::RandomMachine::getRange(0, 3);
        game_.pushState<WritingGame>(game_, articlesFiles[pick]);
    });

    auto bquit = std::make_unique<fw::gui::Button>();
    bquit->setText("Quit");
    bquit->setFunction([&] ()
    {
        game_.closeWindow();
    });

    menu_.addWidget(std::move(b));
    menu_.addWidget(std::move(b2));
    menu_.addWidget(std::move(b3));
    menu_.addWidget(std::move(b4));
    menu_.addWidget(std::move(bquit));
}

void MainMenu::handleEvents(sf::Event e)
{
    menu_.handleEvent(e, game_.getWindow());

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.closeWindow();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        else if (e.key.code == sf::Keyboard::F1)
            metronome_.toggle();
        break;
    default:
        break;
    }
}

void MainMenu::update(sf::Time deltaTime)
{
	metronome_.update(deltaTime);
}

void MainMenu::draw(sf::RenderTarget& renderer)
{
    menu_.draw(renderer);
}

}
