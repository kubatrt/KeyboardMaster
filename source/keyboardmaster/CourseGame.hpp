#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <locale>
#include <codecvt>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "frameworkLib/StateBase.hpp"
#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/Utilities.hpp"
#include "VirtualKeyboard.hpp"
#include "Dictionary.hpp"
#include "KeyboardTyper.hpp"
#include "Misc.hpp"
#include "SoundPlayer.hpp"
#include "Metronome.hpp"

namespace km
{

namespace fw = framework;


class CourseGame : public fw::StateBase
{
public:
    CourseGame(fw::GameBase& game, std::string dictionaryFilePath);
    ~CourseGame();

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

private:
    void textEnteredEvent(wchar_t typedLetter);

    void newLine();
    void prepareTextFields();
    //uint inpenultimateLineNumber(); // index
    //uint currentLineLength();

    sf::Font mainFont_;
    sf::Sprite backgroundSpriteUI_;
    sf::Text nextLetterTextUI_;
    sf::Text debugTextUI_;
    sf::Text gameOverTextUI_;
    std::vector<sf::Text> courseTextUI_;
    std::vector<sf::Text> courseInputTextUI_;

    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    sf::Sprite panelUI_;
    sf::Clock timer_;
    Dictionary dictionary_;
    VirtualKeyboard vkb_;
    KeyboardTyper kb_;
    Metronome metronome_;
    bool gameOver_ = false;

    wchar_t nextLetter_;
    std::wstring typingTextLine_;
    unsigned int currentLine_ = 0;
    unsigned int currentletterInLine_ = 0;
};

}

