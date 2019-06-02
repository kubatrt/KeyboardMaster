#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace framework
{

// Interface for components
// Components can be added in to two places
// NOT TRUE?
// - GameBase - application level, persist through all game states
// - StateBase - persist during active state
struct IGameComponent
{
	virtual ~IGameComponent() = default;
	virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
};

using GameComponentPtr = std::unique_ptr<IGameComponent>;
using GameComponentCPtr = std::unique_ptr<const IGameComponent> ;
using GameComponenSPtr = std::shared_ptr<IGameComponent>;

}
