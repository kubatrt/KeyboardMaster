#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameComponent.hpp"

namespace framework
{

// Basic game component usage example.
class FPSCounter : public IGameComponent
{
public:
	FPSCounter();
	~FPSCounter() = default;

	void update(sf::Time deltaTime) override;
	void draw(sf::RenderTarget& renderer) override;

private:
	sf::Clock delayTimer_;
	sf::Clock fpsTimer_;
	float fps_ = 0.f;
	unsigned int frameCount_ = 0;

	sf::Text textUI_;
};

}
