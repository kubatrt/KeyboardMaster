#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameComponent.hpp"

namespace framework
{

class FPSCounter : IGameComponent
{
    public:
        FPSCounter();

        void update(sf::Time deltaTime) override;
        void draw(sf::RenderTarget& renderer) override;

    private:
        sf::Text textUI_;

        sf::Clock delayTimer_;
        sf::Clock fpsTimer_;
        float fps_ = 0;
        int frameCount_ = 0;
};

}