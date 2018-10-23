#pragma once

#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "Picture.hpp"
#include "Scheduler.hpp"

namespace km
{

namespace fw = framework;

class GalleryGame : public fw::StateBase
{
public:
    GalleryGame(fw::GameBase& game, sf::Vector2u division);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

    void textEnteredEvent();
    void enterWord();

private:
    Picture picture_;
    wchar_t typedLetter_;
    std::wstring typedWord_;
    uint typedWords_= 0;
    bool gameOver_ = false;

    sf::Text gameOverTextUI_;
};

}