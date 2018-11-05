#pragma once

#include <SFML/Graphics.hpp>
#include "frameworkLib/Util/FPSCounter.hpp"
#include "frameworkLib/StateBase.hpp"
#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{
namespace fw = framework;

class KeyboardMaster : public fw::GameBase
{
public:
    KeyboardMaster();

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;
    void handleEvents() override;

private:
    //fw::FPSCounter fpsCounter_;
};

}
