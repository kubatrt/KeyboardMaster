 #pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "frameworkLib/Util/FPSCounter.hpp"
#include "frameworkLib/StateBase.hpp"
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/GameBase.hpp"

namespace example
{
namespace fw = framework;

class CatchGame : public fw::GameBase
{
public:
    CatchGame();

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;
    void handleEvents() override;
private:

    // game components
    fw::FPSCounter fpsCounter_; 
};

}
