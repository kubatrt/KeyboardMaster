#include <algorithm>
#include "GameSate.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"

namespace example
{

GameState::GameState(fw::GameBase& game)
    : StateBase(game)
    , player_({ game_.getWindow().getSize().x / 2.f, game_.getWindow().getSize().y - 60.f })
    , dropLastTime_(sf::Time::Zero)
    , dropInterval_(sf::seconds(2.f))
{

    dropBox({100.f, 30.f}, 2.0f);
    dropBox({game.getWindow().getSize().x - 100.f, 30.f }, 2.5f);

    scoreText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    scoreText_.setCharacterSize(24);
    scoreText_.setStyle(sf::Text::Regular);
    scoreText_.setPosition({10.f, 100.f});
    scoreText_.setString("Score: 0");

    livesText_.setFont(framework::ResourceHolder::get().fonts.get("arial"));
    livesText_.setCharacterSize(24);
    livesText_.setStyle(sf::Text::Regular);
    livesText_.setPosition({10.f, 130.f});
    livesText_.setString("Lives: 0");
}

void GameState::handleEvents(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
        {
            std::cout << "quit" << std::endl;
            game_.popState();
        }
    default:
        break;
    }
}

void GameState::dropBox(sf::Vector2f position, float speed)
{
    Box box{ position, speed };
    boxes_.push_back(box);   // by copy
}

void GameState::checkCollisions()
{
    for (auto& box : boxes_)
    {
        if (collision2d(Point{box.left(), box.bottom()}, player_.rect) ||
            collision2d(Point{box.right(), box.bottom() }, player_.rect))
        {
            box.destroyed = true;
            player_.score += 100;
        }
        else if (box.bottom() >= game_.getWindow().getSize().y )
        {
            box.destroyed = true;
            player_.lives--;
        }
    }
}

void GameState::destroyBoxes()
{
    boxes_.erase(std::remove_if(boxes_.begin(), boxes_.end(), 
        [](auto& box){ return box.destroyed; }), boxes_.end());
}

void GameState::update(sf::Time deltaTime)
{
    dropLastTime_ += deltaTime;
    if (dropLastTime_ > dropInterval_)
    {
        {
            int min = 0 + (Box::size / 2);
            int max = game_.getWindow().getSize().x - Box::size;
            float positionX = static_cast<float>(fw::RandomMachine::getRange<int>(min, max));
            float speed = static_cast<float>(fw::RandomMachine::getRange<int>(1, 4));
            dropBox({positionX, 30.f}, speed);
        }
        dropLastTime_ = sf::Time::Zero;
    }

    player_.update();
    for (auto& box : boxes_)
    {
        box.update(deltaTime);
    }

    checkCollisions();
    destroyBoxes();

    if (player_.lives <= 0)
    {
        std::cout << "Game score: " << player_.score << std::endl;
        game_.popState();
    }

    scoreText_.setString("Score: " + std::to_string(player_.score));
    livesText_.setString("Lives: " + std::to_string(player_.lives));
}

void GameState::draw(sf::RenderTarget& renderer)
{
    for (auto& box : boxes_)
    {
        renderer.draw(box.shape);
    }
    renderer.draw(player_.rect.shape);

    renderer.draw(scoreText_);
    renderer.draw(livesText_);
}

}
