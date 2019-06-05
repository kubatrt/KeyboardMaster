#include "CourseMenu.hpp"
#include "MainMenu.hpp"
#include "CourseGame.hpp"
#include "frameworkLib/GUI/Button.hpp"
#include "Assets.hpp"

namespace km
{

namespace
{
float menuSidePositionOffset = 200.f;
float menuTopPositionOffset = 50.f;
}

CourseMenu::CourseMenu(fw::GameBase& game)
    : StateBase(game)
    , menuLeft_({ game.getWindow().getSize().x / 2.f - menuSidePositionOffset, menuTopPositionOffset })
    , menuRight_({ game.getWindow().getSize().x / 2.f + menuSidePositionOffset, menuTopPositionOffset })
{
	std::vector< std::unique_ptr<fw::gui::Button> > buttons;
	buttons.reserve(courseLessonsFilesCount);

	for(int i = 0; i < courseLessonsFilesCount; ++i)
	{
		auto button = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
		std::ostringstream oss;
		oss << "Lekcja " << std::to_string(i + 1);
		button->setText(oss.str());
		button->setFunction( [=]() {
			LOG_DEBUG("Button " << courseLessonsFiles[i].c_str());
			game_.pushState<CourseGame>(game_, courseLessonsFiles[i]);
		});

		// split buttons into two columns
		if(i < 10)
			menuLeft_.addWidget(std::move(button));
		else
			menuRight_.addWidget(std::move(button));
	}
}

void CourseMenu::handleEvents(sf::Event e)
{
    menuLeft_.handleEvent(e, game_.getWindow());
    menuRight_.handleEvent(e, game_.getWindow());

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.popState();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;
    default:
        break;
    }
}

void CourseMenu::update(sf::Time deltaTime)
{

}

void CourseMenu::draw(sf::RenderTarget& renderer)
{
    menuLeft_.draw(renderer);
    menuRight_.draw(renderer);
}

}
