#include "CourseMenu.hpp"
#include "MainMenu.hpp"
#include "CourseGame.hpp"
#include "frameworkLib/GUI/Button.hpp"
//#include "Assets.hpp"

namespace km
{

namespace
{
float menuSidePositionOffset = 200.f;
float menuTopPositionOffset = 50.f;

constexpr uint courseLessonsFilesCount = 20;
AssetName courseLessonsFiles[] = {
		"data/texts-pl-2.txt",
		"data/course/course_02.txt",
		"data/course/course_03.txt",
		"data/course/course_04.txt",
		"data/course/course_05.txt",
		"data/course/course_06.txt",
		"data/course/course_07.txt",
		"data/course/course_08.txt",
		"data/course/course_09.txt",
		"data/course/course_10.txt",
		"data/course/course_11.txt",
		"data/course/course_12.txt",
		"data/course/course_13.txt",
		"data/course/course_14.txt",
		"data/course/course_15.txt",
		"data/course/course_16.txt",
		"data/course/course_17.txt",
		"data/course/course_18.txt",
		"data/course/course_19.txt",
		"data/course/course_20.txt"
};
}

CourseMenu::CourseMenu(fw::GameBase& game)
    : StateBase(game)
    , menuLeft_({ game.getWindow().getSize().x / 2.f - menuSidePositionOffset, menuTopPositionOffset })
    , menuRight_({ game.getWindow().getSize().x / 2.f + menuSidePositionOffset, menuTopPositionOffset })
{
	backgroundSprite_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

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
	renderer.draw(backgroundSprite_);
    menuLeft_.draw(renderer);
    menuRight_.draw(renderer);
}

}
