#pragma once

#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace example
{

namespace fw = framework;

// Game helpers
struct Point
{
    float x;
    float y;
};

struct Rectangle
{
    sf::RectangleShape shape;

    float x() const noexcept { return shape.getPosition().x; }
    float y() const noexcept { return shape.getPosition().y; }
    float left() const noexcept { return x() - shape.getSize().x / 2.f; }
    float right() const noexcept { return x() + shape.getSize().x / 2.f; }
    float top() const noexcept { return y() - shape.getSize().y / 2.f; }
    float bottom() const noexcept { return y() + shape.getSize().y / 2.f; }
};

template <typename TPoint, typename TRect>
bool collision2d(TPoint a, TRect b)
{
    return (a.x > b.left() && a.x < b.right()) &&
        (a.y >= b.top() && a.y < b.bottom());
}

//-----------------------------------------------------------------------------

// Game logic implementation within state
class GameState : public fw::StateBase
{
public:
    GameState(fw::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    void dropBox(sf::Vector2f position, float speed);
    void destroyBoxes();
    void checkCollisions();
    
    struct Box : public Rectangle   // inheritance?
    {
        static const unsigned size = 48;

        float speed;
        bool destroyed;

        Box(sf::Vector2f position, float speed)
        {
            destroyed = false;
            this->speed = speed;
            shape.setPosition(position);
            shape.setSize( sf::Vector2f{
                static_cast<float>(size), static_cast<float>(size) });
            shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
            shape.setFillColor(sf::Color::Red);
        }

        void update(sf::Time deltaTime)
        {
            sf::Vector2f velocity{ 0.f, speed };
            shape.move(velocity);
        }
    };

    struct Player
    {
        Rectangle rect; // or composition?
        const float playerWidth = 200.f;
        
        unsigned lives;
        unsigned score;
        float speed;
        sf::Vector2f velocity;

        Player(sf::Vector2f position)
        {
            rect.shape = sf::RectangleShape{ sf::Vector2f(playerWidth, 40.f) };
            rect.shape.setPosition(position);
            rect.shape.setOrigin(rect.shape.getSize().x / 2.f, rect.shape.getSize().y / 2.f);
            rect.shape.setFillColor(sf::Color::Blue);
            lives = 3;
            speed = 20.f;
            score = 0;
        }

        void update()
        {
            rect.shape.move(velocity);

            sf::Vector2f v;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rect.left() > 0)
            {
                v.x = -speed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                v.x = speed;
            }
            else
                v.x = 0;

            velocity = v;
        }

    };

    Player player_;
    std::vector<Box> boxes_;
    sf::Time dropLastTime_;
    sf::Time dropInterval_;

    sf::Font font_;
    sf::Text scoreText_;
    sf::Text livesText_;
};

}
