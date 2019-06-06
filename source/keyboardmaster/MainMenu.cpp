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
#include "Assets.hpp"

namespace km
{

namespace
{
constexpr uint GalleryGameRows = 3;
constexpr uint GalleryGameColumns = 2;

}

MainMenu::MainMenu(fw::GameBase& game)
    : StateBase(game)
    , menu_({ game.getWindow().getSize().x / 2.f, 90.f })
{
	LOG_DEBUG("MainMenu CTOR");
	backgroundSprite_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

	informationText_.setFont(fw::ResourceHolder::get().fonts.get("CourierNew"));
	informationText_.setFillColor(sf::Color::White);
	informationText_.setPosition(20, 600);
	informationText_.setString("F1 włącz metronom\nF12 - pełny ekran");

    auto buttonCourse = std::make_unique<fw::gui::Button>();
    buttonCourse->setText("Go to course");
    buttonCourse->setFunction([&] ()
    {
        game_.pushState<CourseMenu>(game_);
    });

    auto buttonWordsAttack = std::make_unique<fw::gui::Button>();
    buttonWordsAttack->setText("Words attack!");
    buttonWordsAttack->setFunction([&] ()
    {
        game_.pushState<WordsAttackGame>(game_);
    });

    auto buttonGallery = std::make_unique<fw::gui::Button>();
    buttonGallery->setText("Gallery");
    buttonGallery->setFunction([&] ()
    {
    	auto randomPicture = framework::RandomMachine::getRange<int>(0, pictureFilesCount - 1);
        game_.pushState<GalleryGame>(game_, GalleryGameRows, GalleryGameColumns,
        		pictureFiles[randomPicture]);
    });


    auto buttonWriting = std::make_unique<fw::gui::Button>();
    buttonWriting->setText("Writing");
    buttonWriting->setFunction([&] ()
    {
        auto randomArticle = fw::RandomMachine::getRange<int>(0, articleFilesCount - 1);
        game_.pushState<WritingGame>(game_, articleFiles[randomArticle]);
    });

    auto buttonQuit = std::make_unique<fw::gui::Button>();
    buttonQuit->setText("Quit");
    buttonQuit->setFunction([&] ()
    {
        game_.closeWindow();
    });

    menu_.addWidget(std::move(buttonCourse));
    menu_.addWidget(std::move(buttonWordsAttack));
    menu_.addWidget(std::move(buttonGallery));
    menu_.addWidget(std::move(buttonWriting));
    menu_.addWidget(std::move(buttonQuit));
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
	renderer.draw(backgroundSprite_);
    menu_.draw(renderer);
}

}
