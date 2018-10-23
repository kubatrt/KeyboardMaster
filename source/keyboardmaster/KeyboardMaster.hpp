#pragma once

#include <SFML/Graphics.hpp>
#include "../FrameworkLib/Util/FPSCounter.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/Utilities.hpp"

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
