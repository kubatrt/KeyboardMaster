 #pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../FrameworkLib/Util/FPSCounter.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/Utilities.hpp"
#include "../FrameworkLib/GameBase.hpp"

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
