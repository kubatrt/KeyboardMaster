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
constexpr uint GalleryGameColumns = 4;
constexpr wchar_t HelpMessageString[] = L"F1 - włącz\\wyłącz metronom F2 - wolniej F3 - szybciej \nF12 - pełny ekran\nESC - powrót\\wyjście";
}

MainMenu::MainMenu(fw::GameBase& game)
    : StateBase(game)
    , menu_({ game.getWindow().getSize().x / 2.f, 90.f })
	, animator_(sprite_)
{
	LOG_DEBUG("MainMenu CTOR");
	backgroundSprite_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

	// TEST
	auto& idleAnimation = animator_.createAnimation("Idle", "spritestrip", sf::seconds(.5f), true);
	idleAnimation.addFrames(sf::Vector2i(0,0), spriteSize_, 6);


	informationText_.setFont(fw::ResourceHolder::get().fonts.get("CourierNew"));
	informationText_.setFillColor(sf::Color::White);
	informationText_.setPosition(20, 660);
	informationText_.setCharacterSize(18);
	informationText_.setString(HelpMessageString);


    auto buttonCourse = std::make_unique<fw::gui::Button>();
    buttonCourse->setText(L"Idź do kursu");
    buttonCourse->setFunction([&] ()
    {
        game_.pushState<CourseMenu>(game_);
    });

    auto buttonWordsAttack = std::make_unique<fw::gui::Button>();
    buttonWordsAttack->setText(L"Atak słów!");
    buttonWordsAttack->setFunction([&] ()
    {
        game_.pushState<WordsAttackGame>(game_, "data/words_01");
    });

    auto buttonGallery = std::make_unique<fw::gui::Button>();
    buttonGallery->setText(L"Galeria");
    buttonGallery->setFunction([&] ()
    {
    	auto randomPicture = framework::RandomMachine::getRange<int>(0, pictureFilesCount - 1);
        game_.pushState<GalleryGame>(game_, GalleryGameRows, GalleryGameColumns,
        		pictureFiles[randomPicture], "data/words_01");
    });

    auto buttonWriting = std::make_unique<fw::gui::Button>();
    buttonWriting->setText(L"Praktyka pisania");
    buttonWriting->setFunction([&] ()
    {
        auto randomArticle = fw::RandomMachine::getRange<int>(0, articleFilesCount - 1);
        game_.pushState<WritingGame>(game_, /*articleFiles[randomArticle]*/ "data/art_02.txt");
    });

    auto buttonQuit = std::make_unique<fw::gui::Button>();
    buttonQuit->setText(L"Wyjdź");
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
	animator_.update(deltaTime);
}

void MainMenu::draw(sf::RenderTarget& renderer)
{
	renderer.draw(backgroundSprite_);
	renderer.draw(informationText_);
	renderer.draw(sprite_);
    menu_.draw(renderer);
}

}
