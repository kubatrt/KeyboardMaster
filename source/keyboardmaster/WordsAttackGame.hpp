#pragma once

#include "../FrameworkLib/GameBase.hpp"
#include "../FrameworkLib/StateBase.hpp"
#include "WordBlock.hpp"
#include "Dictionary.hpp"

namespace km
{

namespace fw = framework;

class WordsAttackGame : public fw::StateBase
{
public:
    WordsAttackGame(fw::GameBase& game);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

    void textEnteredEvent(wchar_t letter);
    void enterWord(std::wstring word);

private:
    void spawnWordBlock();
    void destroyWord();

    std::vector<std::shared_ptr<WordBlock>> wordBlocks_;
    Dictionary dictionary_;

    wchar_t typedLetter_;
    std::wstring typedWord_;

    int score_ = 0;
    int lives = 3;
    bool gameOver = false;
    int missedWords = 0;
    int maxWordsInGame = 10;
    int wordsInGame = 0;
    

    sf::Clock spawnClock_;
    sf::Time spawnInterval_;

    // GUI
    sf::RectangleShape horizontalLineUI_;
    sf::Text typingTextUI_;
    sf::Text scoreTextUI_;
    sf::Text livesTextUI_;
    sf::Text gameOverTextUI_;
    //std::wstring    typingText_;
};

}
