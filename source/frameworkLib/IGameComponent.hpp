#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace framework
{

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
