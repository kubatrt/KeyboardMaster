#include <iostream>
#include "FPSCounter.hpp"
#include "../ResourceManager/ResourceHolder.hpp"

namespace framework
{

FPSCounter::FPSCounter()
{
    textUI_.move(10, 10);
    textUI_.setOutlineColor (sf::Color::Black);
    textUI_.setFillColor(sf::Color::Yellow);
    textUI_.setOutlineThickness(2);
    textUI_.setFont(ResourceHolder::get().fonts.get("arial"));
    textUI_.setCharacterSize(24);
}


void FPSCounter::update(sf::Time deltaTime)
{
    frameCount_++;

    if (delayTimer_.getElapsedTime().asSeconds() > 0.2)
    {
        fps_ = frameCount_ / fpsTimer_.restart().asSeconds();
        frameCount_ = 0;
        delayTimer_.restart();
    }
}

void FPSCounter::draw(sf::RenderTarget& renderer)
{
    textUI_.setString("FPS: " + std::to_string((int)fps_));
    renderer.draw(textUI_);
}

}