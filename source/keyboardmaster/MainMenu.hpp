#pragma once

#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/StateBase.hpp"
#include "frameworkLib/GUI/StackMenu.hpp"
#include "frameworkLib/Util/Animation.hpp"
#include "Metronome.hpp"

namespace km
{

namespace fw = framework;

class MainMenu : public fw::StateBase
{
public:
    MainMenu(fw::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    fw::gui::StackMenu menu_;
    Metronome metronome_;	// TODO: test metronome
    //fw::Animation animation_; TODO: test animation
};

}
