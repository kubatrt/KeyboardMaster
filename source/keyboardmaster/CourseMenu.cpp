#include "CourseMenu.hpp"
#include "MainMenu.hpp"
#include "CourseGame.hpp"

#include "../FrameworkLib/GUI/Button.hpp"

namespace km
{

CourseMenu::CourseMenu(fw::GameBase& game)
    : StateBase(game)
    , menuLeft_({ game.getWindow().getSize().x / 2.f - 200.f, 50.f })
    , menuRight_({ game.getWindow().getSize().x / 2.f + 200.f, 50.f })
{
    auto b01 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b01->setText("Lekcja 01");
    b01->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\texts-pl-2.txt");
    });
    auto b02 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b02->setText("Lekcja 02");
    b02->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_02.txt");
    });
    auto b03 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b03->setText("Lekcja 03");
    b03->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_03.txt");
    });
    auto b04 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b04->setText("Lekcja 04");
    b04->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_04.txt");
    });
    auto b05 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b05->setText("Lekcja 05");
    b05->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_05.txt");
    });
    auto b06 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b06->setText("Lekcja 06");
    b06->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_06.txt");
    });
    auto b07 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b07->setText("Lekcja 07");
    b07->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_07.txt");
    });
    auto b08 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b08->setText("Lekcja 08");
    b08->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_08.txt");
    });
    auto b09 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b09->setText("Lekcja 09");
    b09->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_09.txt");
    });
    auto b10 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b10->setText("Lekcja 10");
    b10->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_10.txt");
    });

    auto b11 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b11->setText("Lekcja 11");
    b11->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_11.txt");
    });
    auto b12 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b12->setText("Lekcja 12");
    b12->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_12.txt");
    });
    auto b13 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b13->setText("Lekcja 13");
    b13->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_13.txt");
    });
    auto b14 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b14->setText("Lekcja 14");
    b14->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_14.txt");
    });
    auto b15 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b15->setText("Lekcja 15");
    b15->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_15.txt");
    });
    auto b16 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b16->setText("Lekcja 16");
    b16->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_16.txt");
    });
    auto b17 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b17->setText("Lekcja 17");
    b17->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_17.txt");
    });
    auto b18 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b18->setText("Lekcja 18");
    b18->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_18.txt");
    });
    auto b19 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b19->setText("Lekcja 19");
    b19->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_19.txt");
    });
    auto b20 = std::make_unique<fw::gui::Button>(fw::gui::ButtonSize::Thin);
    b20->setText("Lekcja 20");
    b20->setFunction([&] ()
    {
        game_.pushState<CourseGame>(game_, "D:\\Workspace\\Projects\\Framework\\Debug\\data\\course_20.txt");
    });

    menuLeft_.addWidget(std::move(b01));
    menuLeft_.addWidget(std::move(b02));
    menuLeft_.addWidget(std::move(b03));
    menuLeft_.addWidget(std::move(b04));
    menuLeft_.addWidget(std::move(b05));
    menuLeft_.addWidget(std::move(b06));
    menuLeft_.addWidget(std::move(b07));
    menuLeft_.addWidget(std::move(b08));
    menuLeft_.addWidget(std::move(b09));
    menuLeft_.addWidget(std::move(b10));
    menuRight_.addWidget(std::move(b11));
    menuRight_.addWidget(std::move(b12));
    menuRight_.addWidget(std::move(b13));
    menuRight_.addWidget(std::move(b14));
    menuRight_.addWidget(std::move(b15));
    menuRight_.addWidget(std::move(b16));
    menuRight_.addWidget(std::move(b17));
    menuRight_.addWidget(std::move(b18));
    menuRight_.addWidget(std::move(b19));
    menuRight_.addWidget(std::move(b20));
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