#pragma once

#include <iostream>
#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "VirtualKeyboard.hpp"
#include "Dictionary.hpp"
#include "KeyboardTyper.hpp"
#include "Misc.hpp"

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
    void textEnteredEvent(wchar_t typedLetter);
    void newLine();

    sf::Clock timer_;
    sf::Font mainFont_;
    Dictionary dictionary_;
    KeyboardTyper kb_;
    bool gameOver_;

    sf::Text debugTextUI_;
    std::vector<sf::Text> courseTextUI_;
    std::vector<sf::Text> courseInputTextUI_;

    wchar_t nextLetter_ = 0;
    std::wstring typingTextLine_;
    unsigned int currentLine_ = 0;
    unsigned int currentletterInLine_ = 0;
};

}

