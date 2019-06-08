#pragma once

#include <iostream>
#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/StateBase.hpp"
#include "VirtualKeyboard.hpp"
#include "Dictionary.hpp"
#include "KeyboardTyper.hpp"
#include "Misc.hpp"
#include "Metronome.hpp"

namespace km
{

namespace fw = framework;

class WritingGame : public fw::StateBase
{
public:
    WritingGame(fw::GameBase& game, std::string dictionaryFile);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    std::wstring prepareStatusString();
    void textEnteredEvent(wchar_t typedLetter);
    void newLine();
    void setNextLetter();

    sf::Time gameTime_;
    sf::Font mainFont_;
    Dictionary dictionary_;
    KeyboardTyper kb_;
    Metronome metronome_;
    bool gameOver_;

    sf::Sprite backgroundSpriteUI_;
    sf::RectangleShape panelRectUI_;
    sf::Text statusTextUI_;
    sf::Text nextLetterTextUI_;
    std::vector<sf::Text> courseTextUI_;
    std::vector<sf::Text> courseInputTextUI_;

    wchar_t nextLetter_ = 0;
    std::wstring typingTextLine_;
    unsigned int currentLine_ = 0;
    unsigned int currentletterInLine_ = 0;
};

}

